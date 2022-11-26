#include <iostream>
#include <winsock2.h>
#include <thread>
#include "tank.h"
#include "util.h"
#include <string>
using namespace std;

#define PACKET_SIZE 1024
SOCKET skt, client_sock;

int isMyTurn = 1;

void upStrength() {
    if (str < 6) {
        str++;
        for (int i = mapsero + 1; i < mapsero + 6; i++) {
            for (int j = 74; j < 74 + str * 12; j++) {
                if ((j - 74) % 12 != 0) {
                    goToPoint(j, i);
                    drw(YELLOW, YELLOW);
                    printf(" ");
                    drw(BLACK, BLACK);
                }
                else {
                    goToPoint(j, i);
                    drw(BLACK, BLACK);
                    printf(" ");
                }
            }
        }
    }
}

void downStrength() {
    if (str > 1) {
        for (int i = 74 + str * 12; i >= 74 + (str - 1) * 12; i--) {
            for (int j = mapsero + 1; j < mapsero + 6; j++) {
                goToPoint(i, j);
                drw(BLACK, BLACK);
                printf(" ");
            }
        }
        str--;
    }
}

void proc_recvs() {
    char buffer[PACKET_SIZE] = { 0 };

    while (!WSAGetLastError()) {
        ZeroMemory(&buffer, PACKET_SIZE);
        recv(client_sock, buffer, PACKET_SIZE, 0);

        if (buffer[0] == '2') {
            if (buffer[1] == '1') {
                if (buffer[2] == '1') {
                    moveTank2Left();
                }
                else {
                    moveTank2Rignt();
                }
            }
            else if (buffer[1] == '2') {
                if (buffer[2] == '1') {
                    tank2UpAngle();
                }
                else {
                    tank2DownAngle();
                }
            }
            else {
                if (buffer[2] == '1') {
                    isMyTurn = 1;

                    shoot2((int)(buffer[3] - '0'));
                }
            }
        }
    }
}

int main() {

    CursorView(false);

    system("mode con: cols=80 lines=33");
    
    for (int i = 0; i < 33; i++) {
        for (int j = 0; j < 80; j++) {
            if (i == 0 || i == 1|| i == 32 || i == 31) {
                goToPoint(j, i);
                drw(GREEN, GREEN);
                printf(" ");
                drw(BLACK, BLACK);
            }
            if (j == 0 || j == 1 || j == 2 || j == 79 || j == 78 || j == 77) {
                goToPoint(j, i);
                drw(GREEN, GREEN);
                printf(" ");
                drw(BLACK, BLACK);
            }
        }
    }

    for (int i = 0; i < 33; i++) {
        for (int j = 0; j < 80; j++) {
            if (startPage[i][j] == 1) {
                goToPoint(j, i);
                drw(LIGHTGREEN, LIGHTGREEN);
                printf(" ");
                drw(BLACK, BLACK);
            }
        }
    }
    
    goToPoint(30, 25);
    drw(BLACK, WHITE);
    printf("Waiting for CLIENT :)");
    drw(BLACK, BLACK);

    WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	skt = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4444);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
bind(
	skt, (SOCKADDR*)&addr, sizeof(addr));
	listen(skt, SOMAXCONN);

	SOCKADDR_IN client = {};
	int client_size = sizeof(client);
	ZeroMemory(&client, client_size);
	client_sock = accept(skt, (SOCKADDR*)&client, &client_size);
    
    char buffer[PACKET_SIZE] = "";
	thread proc2(proc_recvs);
    
    system("mode con: cols=149 lines=48");
    printMap();

    upStrength();
    makeTank(tankX, tankY);
    make2Tank(tank2X, tank2Y);

    printHP();

    while (1) {
        buffer[0] = '\0';
        
        Sleep(500);
            if (isMyTurn == 1) {
                Sleep(500);
                while (1) {
                    if (GetAsyncKeyState(VK_LEFT)) {
                        strcpy(buffer, "111");
                        send(client_sock, buffer, strlen(buffer), 0);
                        
                        moveTankLeft();
                    }
                    if (GetAsyncKeyState(VK_RIGHT)) {
                        strcpy(buffer, "112");
                        send(client_sock, buffer, strlen(buffer), 0);
                        
                        moveTankRignt();
                    }
                    if (GetAsyncKeyState(VK_SPACE)) {
                        isMyTurn++;
                        Sleep(500);
                        break;
                    }
                }
            }

            if (isMyTurn == 2) {
                while (1) {
                    if (GetAsyncKeyState(VK_UP)) {
                        strcpy(buffer, "121");
                        send(client_sock, buffer, strlen(buffer), 0);
                        tankUpAngle();
                    }
                    if (GetAsyncKeyState(VK_DOWN)) {
                        strcpy(buffer, "122");
                        send(client_sock, buffer, strlen(buffer), 0);
                        tankDownAngle();
                    }
                    if (GetAsyncKeyState(VK_SPACE)) {
                        isMyTurn++;
                        Sleep(500);
                        break;
                    }
                }
            }

            if (isMyTurn == 3) {
                while (1) {
                    if (GetAsyncKeyState(VK_RIGHT)) {
                        upStrength();
                        Sleep(100);
                    }
                    if (GetAsyncKeyState(VK_LEFT)) {
                        downStrength();
                        Sleep(100);
                    }
                    if (GetAsyncKeyState(VK_SPACE)) {
                        isMyTurn = 0;
                        char a[4] = "131";
                        char b[2] = { str + '0' };
                        strcpy(buffer, strcat(a, b));

                        send(client_sock, buffer, strlen(buffer), 0);
                        shoot(str);
                        Sleep(500);
                        
                        break;
                    }
                }
            }

        
    }
    proc2.join();
    closesocket(client_sock);
    closesocket(skt);
    WSACleanup();
}