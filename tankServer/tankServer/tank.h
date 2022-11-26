#ifndef TANK_H_INCLUDED
#define TANK_H_INCLUDED
#define mapgaro 149
#define mapsero 41
#define tankGaro 8
#define tankSero 7
#include "util.h"
#include <iostream>
#include <synchapi.h>
int tankColor = 10;
int tank2Color = 4;
int tankX = 7;
int tankY = 38;
int tank2X = 148;
int tank2Y = 38;
int tankAngle = 0;
int tank2Angle = 0;
int str = 0;
int bulletSpeed = 20;
int tank[5][tankSero][tankGaro] = {
    {
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1},
    {1,1,1,1,1,0,0,0},
    {1,2,2,2,1,0,0,0}
    },
    {
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1},
    {0,1,1,1,1,1,1,0},
    {1,1,1,1,1,0,0,0},
    {1,2,2,2,1,0,0,0}
    },
    {
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,1,0},
    {0,1,1,1,1,1,0,0},
    {1,1,1,1,1,0,0,0},
    {1,2,2,2,1,0,0,0}
    },
    {
    {0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,1,0},
    {0,0,0,0,0,1,0,0},
    {0,1,1,1,1,0,0,0},
    {1,1,1,1,1,0,0,0},
    {1,2,2,2,1,0,0,0}
    }
};

int tank2[5][tankSero][tankGaro] = {
    {
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,0},
    {0,0,0,1,1,1,1,1},
    {0,0,0,1,2,2,2,1}
    },
    {
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,0},
    {0,0,0,1,1,1,1,1},
    {0,0,0,1,2,2,2,1}
    },
    {
    {0,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {0,1,0,0,0,0,0,0},
    {0,0,1,1,1,1,1,0},
    {0,0,0,1,1,1,1,1},
    {0,0,0,1,2,2,2,1}
    },
    {
    {1,0,0,0,0,0,0,0},
    {0,1,0,0,0,0,0,0},
    {0,0,1,0,0,0,0,0},
    {0,0,0,1,1,1,1,0},
    {0,0,0,1,1,1,1,1},
    {0,0,0,1,2,2,2,1}
    }
};

void makeTank(int x,int y) {
    x -= tankGaro-1;
    y -= tankSero-1;
    for (int i = y; i < y + tankSero; i++) {
        for (int j = x; j < x + tankGaro; j++) {
            if (tank[tankAngle][i - y][j - x] == 1) {
                goToPoint(j, i);
                drw(tankColor, tankColor);
                printf(" ");
                drw(CYAN, CYAN);
            }
            else if (tank[tankAngle][i - y][j - x] == 2) {
                goToPoint(j, i);
                drw(BLACK, BLACK);
                printf(" ");
                drw(CYAN, CYAN);
            }
        }
    }
}


void make2Tank(int x, int y) {
    x -= tankGaro - 1;
    y -= tankSero - 1;
    for (int i = y; i < y + tankSero; i++) {
        for (int j = x; j < x + tankGaro; j++) {
            if (tank2[tank2Angle][i - y][j - x] == 1) {
                goToPoint(j, i);
                drw(tank2Color, tank2Color);
                printf(" ");
                drw(CYAN, CYAN);
            }
            else if (tank2[tank2Angle][i - y][j - x] == 2) {
                goToPoint(j, i);
                drw(BLACK, BLACK);
                printf(" ");
                drw(CYAN, CYAN);
            }
        }
    }
}


void deleteTank(int x,int y) {
    x -= tankGaro-1;
    y -= tankSero;
    for (int i = y; i < y+tankSero; i++) {
        for (int j = x; j < x+tankGaro; j++) {
            goToPoint(j, i);
            drw(CYAN, CYAN);
            printf(" ");
            drw(CYAN, CYAN);
        }
    }
}

void moveTankLeft() {
        if(tankX -3 >4) {
            deleteTank(tankX, tankY);
            tankX--;
            makeTank(tankX,tankY);
            Sleep(100);
        }
    
}

void moveTankRignt() {
        if(tankX +1 < 53) {
            deleteTank(tankX,tankY);
            tankX++;
            makeTank(tankX,tankY);
            Sleep(100);
        }
    
}

void tankUpAngle() {
    if(tankAngle < 3) {
        tankAngle++;
        deleteTank(tankX,tankY);
        makeTank(tankX,tankY);
        Sleep(100);
    }
}

void tankDownAngle() {
    if(tankAngle > 0) {
        tankAngle--;
        deleteTank(tankX,tankY);
        makeTank(tankX,tankY);
        Sleep(100);
    }
}

void shootByAngle(int x, int y, int garo, int sero, int strength) {
    for (int i = 0; i < 2; i++) {
        for (int j = 1; j <= sero * strength; j++) {

            x++;
            y--;
            if (map[y][x] != 0) return;
            if (y >= mapsero - 1) return;
            goToPoint(x, y);
            drw(YELLOW, YELLOW);
            printf(" ");
            drw(CYAN, CYAN);
            if (x != tankX + 1 && y != tankY - 5) {
                goToPoint(x - 1, y + 1);
                drw(CYAN, CYAN);
                printf(" ");
                drw(CYAN, CYAN);
                Sleep(bulletSpeed);
            }

        }
        for (int j = 1; j <= garo * strength; j++) {
            x += 1;
            if (map[y][x] != 0) return;
            if (y >= mapsero - 1) return;
            goToPoint(x, y);
            drw(YELLOW, YELLOW);
            printf(" ");
            drw(CYAN, CYAN);
            goToPoint(x - 1, y);
            drw(CYAN, CYAN);
            printf(" ");
            drw(CYAN, CYAN);

            Sleep(bulletSpeed);
        }
    }


    while (1) {
        if (map[y][x] != 0) return;
        if (y >= mapsero - 1) return;
        for (int j = 1; j <= sero * strength; j++) {
            x++;
            y++;
            goToPoint(x, y);
            drw(YELLOW, YELLOW);
            printf(" ");
            drw(CYAN, CYAN);
            goToPoint(x - 1, y - 1);
            drw(CYAN, CYAN);
            printf(" ");
            drw(CYAN, CYAN);
            Sleep(bulletSpeed);

            if (x >= tank2X - tankGaro + 1 && x <= tank2X) {
                if (y >= tank2Y - tankSero && y <= tank2Y) {
                    p2HP -= 9;
                    goToPoint(x, y);
                    drw(CYAN, CYAN);
                    printf(" ");
                    drw(CYAN, CYAN);
                    return;
                }
            }

            if (map[y][x] != 0) break;
            if (y >= mapsero - 1) break;
        }
        for (int j = 1; j <= garo * strength; j++) {
            x += 1;
            goToPoint(x, y);
            drw(YELLOW, YELLOW);
            printf(" ");
            drw(CYAN, CYAN);
            goToPoint(x - 1, y);
            drw(CYAN, CYAN);
            printf(" ");
            drw(CYAN, CYAN);

            Sleep(bulletSpeed);
            if (map[y][x] != 0) break;
            if (y >= mapsero - 1) break;
        }
    }
}

void shoot(int strength) {
    if (tankAngle == 0) {
        int x = tankX;
        int y = tankY - 3;
        for (int i = 1; i <= 7 * strength; i++) {
            x += 1;
            goToPoint(x, y);
            drw(YELLOW, YELLOW);
            printf(" ");
            drw(CYAN, CYAN);
            if (i != 1) {
                goToPoint(x - 1, y);
                drw(CYAN, CYAN);
                printf(" ");
                drw(CYAN, CYAN);
            }
            Sleep(bulletSpeed);
        }
        while (1) {
            x += 1;
            y += 1;
            if (map[y][x] != 0) break;
            if (y >= mapsero) break;
            goToPoint(x, y);
            drw(YELLOW, YELLOW);
            printf(" ");
            drw(CYAN, CYAN);

            if (x >= tank2X - tankGaro + 1 && x <= tank2X) {
                if (y >= tank2Y - tankSero && y <= tank2Y) {
                    p2HP -= 9;
                    goToPoint(x, y);
                    drw(CYAN, CYAN);
                    printf(" ");
                    drw(CYAN, CYAN);
                    return;
                }
            }

            goToPoint(x - 1, y - 1);
            drw(CYAN, CYAN);
            printf(" ");
            drw(CYAN, CYAN);
            Sleep(bulletSpeed);

        }
        goToPoint(x - 1, y - 1);
        drw(CYAN, CYAN);
        printf(" ");
        drw(CYAN, CYAN);
        Sleep(bulletSpeed);
    }

    if (tankAngle == 1) {
        int x = tankX;
        int y = tankY - 4;
        int garo = 2;
        int sero = 1;
        shootByAngle(x, y, garo, sero, strength);
    }

    if (tankAngle == 2) {
        int x = tankX;
        int y = tankY - 5;
        int garo = 2;
        int sero = 2;
        shootByAngle(x, y, garo, sero, strength);
    }
    if (tankAngle == 3) {
        int x = tankX;
        int y = tankY - 6;
        int garo = 1;
        int sero = 2;
        shootByAngle(x, y, garo, sero, strength);
    }

    if (p2HP == 0) {
        system("mode con: cols=80 lines=25");
        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 80; j++) {
                goToPoint(j, i);
                if (win[i][j] == 1) {
                    drw(WHITE, WHITE);
                    printf(" ");
                }
                else {
                    drw(BLACK, BLACK);
                    printf(" ");
                }
            }
        }
    }
}



void moveTank2Left() {
        if (tank2X - 3 > 100) {
            deleteTank(tank2X, tank2Y);
            tank2X--;
            make2Tank(tank2X, tank2Y);
            Sleep(100);
        }
    
}

void moveTank2Rignt() {
        if (tank2X + 1 < mapgaro) {
            deleteTank(tank2X, tank2Y);
            tank2X++;
            make2Tank(tank2X, tank2Y);
            Sleep(100);
        }
    
}

void tank2UpAngle() {
    if (tank2Angle < 3) {
        tank2Angle++;
        deleteTank(tank2X, tank2Y);
        make2Tank(tank2X, tank2Y);
        Sleep(100);
    }
}

void tank2DownAngle() {
    if (tank2Angle > 0) {
        tank2Angle--;
        deleteTank(tank2X, tank2Y);
        make2Tank(tank2X, tank2Y);
        Sleep(100);
    }
}

void shootByAngle2(int x, int y, int garo, int sero, int strength) {
    for (int i = 0; i < 2; i++) {
        for (int j = 1; j <= sero * strength; j++) {

            x--;
            y--;
            if (map[y][x] != 0) return;
            if (y >= mapsero - 1) return;
            goToPoint(x, y);
            drw(YELLOW, YELLOW);
            printf(" ");
            drw(CYAN, CYAN);
            if (x != tankX + 1 && y != tankY - 5) {
                goToPoint(x + 1, y + 1);
                drw(CYAN, CYAN);
                printf(" ");
                drw(CYAN, CYAN);
                Sleep(bulletSpeed);
            }

        }
        for (int j = 1; j <= garo * strength; j++) {
            x -= 1;
            if (map[y][x] != 0) return;
            if (y >= mapsero - 1) return;
            goToPoint(x, y);
            drw(YELLOW, YELLOW);
            printf(" ");
            drw(CYAN, CYAN);
            goToPoint(x + 1, y);
            drw(CYAN, CYAN);
            printf(" ");
            drw(CYAN, CYAN);

            Sleep(bulletSpeed);
        }
    }


    while (1) {
        if (map[y][x] != 0) return;
        if (y >= mapsero - 1) return;
        for (int j = 1; j <= sero * strength; j++) {
            x--;
            y++;
            goToPoint(x, y);
            drw(YELLOW, YELLOW);
            printf(" ");
            drw(CYAN, CYAN);
            goToPoint(x + 1, y - 1);
            drw(CYAN, CYAN);
            printf(" ");
            drw(CYAN, CYAN);
            Sleep(bulletSpeed);
            
            if (x >= tankX - tankGaro && x <= tankX) {
                if (y >= tankY - tankSero && y <= tankY) {
                    p1HP -= 9;
                    printHP();
                    goToPoint(x, y);
                    drw(CYAN, CYAN);
                    printf(" ");
                    drw(CYAN, CYAN);
                    return;
                }
            }

            if (map[y][x] != 0) break;
            if (y >= mapsero - 1) break;
        }
        for (int j = 1; j <= garo * strength; j++) {
            x -= 1;
            goToPoint(x, y);
            drw(YELLOW, YELLOW);
            printf(" ");
            drw(CYAN, CYAN);
            goToPoint(x + 1, y);
            drw(CYAN, CYAN);
            printf(" ");
            drw(CYAN, CYAN);

            Sleep(bulletSpeed);
            if (map[y][x] != 0) break;
            if (y >= mapsero - 1) break;
        }
    }
}

void shoot2(int strength) {
    if (tank2Angle == 0) {
        int x = tank2X - tankGaro;
        int y = tank2Y - 3;
        for (int i = 1; i <= 7 * strength; i++) {
            x -= 1;
            goToPoint(x, y);
            drw(YELLOW, YELLOW);
            printf(" ");
            drw(CYAN, CYAN);
            if (i != 1) {
                goToPoint(x + 1, y);
                drw(CYAN, CYAN);
                printf(" ");
                drw(CYAN, CYAN);
            }
            Sleep(bulletSpeed);
        }
        while (1) {
            x -= 1;
            y += 1;
            if (map[y][x] != 0) break;
            if (y >= mapsero) break;
            goToPoint(x, y);
            drw(YELLOW, YELLOW);
            printf(" ");
            drw(CYAN, CYAN);

            goToPoint(x + 1, y - 1);
            drw(CYAN, CYAN);
            printf(" ");
            drw(CYAN, CYAN);
            Sleep(bulletSpeed);

            if (x >= tankX - tankGaro && x <= tankX) {
                if (y >= tankY - tankSero && y <= tankY) {
                    p1HP -= 9;
                    printHP();
                    goToPoint(x, y);
                    drw(CYAN, CYAN);
                    printf(" ");
                    drw(CYAN, CYAN);
                    return;
                }
            }
            
        }
        goToPoint(x + 1, y - 1);
        drw(CYAN, CYAN);
        printf(" ");
        drw(CYAN, CYAN);
        Sleep(bulletSpeed);
    }

    if (tank2Angle == 1) {
        int x = tank2X - tankGaro;
        int y = tank2Y - 4;
        int garo = 2;
        int sero = 1;
        shootByAngle2(x, y, garo, sero, strength);
    }

    if (tank2Angle == 2) {
        int x = tank2X - tankGaro;
        int y = tank2Y - 5;
        int garo = 2;
        int sero = 2;
        shootByAngle2(x, y, garo, sero, strength);
    }
    if (tank2Angle == 3) {
        int x = tank2X - tankGaro;
        int y = tank2Y - 6;
        int garo = 1;
        int sero = 2;
        shootByAngle2(x, y, garo, sero, strength);
    }
    if (p1HP == 0) {
        system("mode con: cols=80 lines=45");
        for (int i = 0; i < 45; i++) {
            for (int j = 0; j < 80; j++) {
                goToPoint(j, i);
                if (lose[i][j] == 1) {
                    drw(WHITE, WHITE);
                    printf(" ");
                }
                else {
                    drw(BLACK, BLACK);
                    printf(" ");
                }
            }
        }
    }
}



#endif // TANK_H_INCLUDED
