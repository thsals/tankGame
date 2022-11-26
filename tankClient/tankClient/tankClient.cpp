#include <iostream>
#include <winsock2.h>
#include <thread>
#include "tank.h"
#include "util.h"
using namespace std;

#pragma comment(lib, "ws2_32.lib")

#define PACKET_SIZE 1024

SOCKET skt;

int isMyTurn2 = 0;

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


void proc_recv() {
    char buffer[PACKET_SIZE] = { 0 };

    while (!WSAGetLastError()) {
        ZeroMemory(&buffer, PACKET_SIZE);
        recv(skt, buffer, PACKET_SIZE, 0);

        if (buffer[0] ==  '1') {
            if (buffer[1] == '1') {
                if (buffer[2] == '1') {
                    moveTankLeft();
                }
                else {
                    moveTankRignt();
                }
            }
            else if (buffer[1] == '2') {
                if (buffer[2] == '1') {
                    tankUpAngle();
                }
                else {
                    tankDownAngle();
                }
            }
            else {
                if (buffer[2] == '1') {
                    isMyTurn2 = 1;
                    shoot((int)(buffer[3] - '0'));
                }
            }
        }
    }
}

int main() {
	system("mode con: cols=149 lines=48");

	CursorView(false);

	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	skt = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4444);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	while (1) {
		if (!connect(skt, (SOCKADDR*)&addr, sizeof(addr))) break;
	}

    char buffer[PACKET_SIZE] = "";
	thread proc1(proc_recv);
	
    printMap();

    upStrength();
    makeTank(tankX, tankY);
    make2Tank(tank2X, tank2Y);

    printHP2();

    while (1) {
        buffer[0] = '\0';
        Sleep(500);

            if (isMyTurn2 == 1) {
                Sleep(500);
                while (1) {
                    if (GetAsyncKeyState(VK_LEFT)) {
                        strcpy(buffer, "211");
                        send(skt, buffer, strlen(buffer), 0);
                        
                        moveTank2Left();
                    }
                    if (GetAsyncKeyState(VK_RIGHT)) {
                        strcpy(buffer, "212");
                        send(skt, buffer, strlen(buffer), 0);
                        
                        moveTank2Rignt();
                    }
                    if (GetAsyncKeyState(VK_SPACE)) {
                        isMyTurn2++;
                        Sleep(500);
                        break;
                    }
                }
            }

            if (isMyTurn2 == 2) {
                while (1) {
                    if (GetAsyncKeyState(VK_UP)) {
                        strcpy(buffer, "221");
                        send(skt, buffer, strlen(buffer), 0);
                        tank2UpAngle();
                    }
                    if (GetAsyncKeyState(VK_DOWN)) {
                        strcpy(buffer, "222");
                        send(skt, buffer, strlen(buffer), 0);
                        tank2DownAngle();
                    }
                    if (GetAsyncKeyState(VK_SPACE)) {
                        isMyTurn2++;
                        Sleep(500);
                        break;
                    }
                }
            }

            if (isMyTurn2 == 3) {
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
                        isMyTurn2 = 0;
                        char a[4] = "231";
                        char b[2] = { str + '0' };
                        strcpy(buffer, strcat(a,b));
                        send(skt, buffer, strlen(buffer), 0);
                        shoot2(str);
                        Sleep(500);
                        break;
                    }
                }
            }

    }


	proc1.join();
	closesocket(skt);
	WSACleanup();
}
