#pragma once

#include "stage1Map.h" 
#include "stage2Map.h"
#include "stage3Map.h"
#include <Windows.h>
#include <time.h>   //���� �Լ� �õ� ���ؼ�
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
// Ŀ���� ��ġ = ĳ������ ��ġ

//���� ����
    //�������� �ʺ�, ����           
int g_stage1Width = 70;
int g_stage1Height = 20;
int g_stage2Width = 70;
int g_stage2Height = 30;
int g_stage3Width = 70;
int g_stage3Height = 30;
    //�������� ���� ��ǥ
COORD g_stage1StartPos = { 2,19 -1 };       //���Ӻ��� y��ǥ�� 0~19�̹Ƿ�     18���� �����ؾ���         
COORD g_stage2StartPos = { 2,29 -1 };
COORD g_stage3StartPos = { 2,29 -1 };

int g_curStage = 1;                 //���� ��������
int g_charSpeed = 50;               //ĳ������ �̵��ӵ�
int g_npcSpeed = 50;                //NPC�� �̵��ӵ�
int g_gravityAccereralte = 250;     //�߷� ���ӵ�        ����(q,w,e)�� ���� �� ���� �ð� Show �ϰ� �ϴ� ����     q,w,e ���� �Լ� ����
int g_fatigue = 0;                  //�Ƿε�

// ���Ӻ��� ����                   �����Ҵ� ��� �׳� �������� �������ִ� ������ ����.
//int g_stage1GameBoardInfo[30][80];									
//int g_stage2GameBoardInfo[30][80];									
//int g_stage3GameBoardInfo[30][80];									
int** g_stage1GameBoardInfo;
int** g_stage2GameBoardInfo;
int** g_stage3GameBoardInfo;

//�Լ� ����
void setCurrentCursorPosition(int x, int y);                            // Ŀ�� ��ġ ����

COORD getCurrentCursorPosition();                                       // Ŀ�� ��ġ ��ȯ

void removeCursor();													// Ŀ��  ������ ����

void processKeyInput();													// Ű �Է¹޴� �޼ҵ�

int detectCollision(int posX, int posY);				            	// �浹 �˻� �Լ�

void initiallize();                                                     // main�Լ� while�� ������ �̸� ���� �Ǿ���ϴ� �Լ���

void fullscreen();                                                      // �ܼ�â ��üȭ��

void drawStageGameBoardInfo();                                          // ���Ӻ��������� �Է��ϴ� �Լ�

int isGameOver();                                                       // �Ƿε��� 100�� �̻��̸� 1�� ����

int gravity();                                                          // �߷�

void reDrawMap();                                                       // �ܼ�â�� �� ������ ������Ʈ

int moveChar(int dx, int dy);                                           //ĳ���͸� (+dx,+dy)��ŭ ������

int jump();                                                             // ��

int shiftLeft();                                                        // ��

int shiftRight();                                                       // ��

int shiftDLeft();                                                       // ��       �ڡڡ�

int shiftDRight();                                                      // ��       �ڡڡ�

//int isNextStage();                                                      // ��Ż�� �浹�ߴ��� �����ϴ� �Լ�

int gotoNextStage();                                                    // ���� ���������� �̵��ϴ� �Լ�

void victory();                                                         // ���� �¸�

int gravityBox(int x, int y);                                           // �ڽ��� �߷��� �����Ű�� �Լ�

void pushBox();                                                         // �ڽ� �б� �Լ�(����üũ)

void push(int x, int y, int dir);                                       // �ڽ��� �̴� �Լ�(����)
//�Լ� ����

void fatigue()
{
    COORD curPos = getCurrentCursorPosition();
    
    setCurrentCursorPosition(20, 0);
    printf("�Ƿε� : %d",g_fatigue);
    setCurrentCursorPosition(curPos.X, curPos.Y);

}
void setCurrentCursorPosition(int x, int y) {                           //Ŀ�� ��ġ ����
    COORD p = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

COORD getCurrentCursorPosition() {                                      //Ŀ�� ��ġ ��ȯ
    CONSOLE_SCREEN_BUFFER_INFO curInfo;
    COORD out;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    out.X = curInfo.dwCursorPosition.X;
    out.Y = curInfo.dwCursorPosition.Y;
    return out;
}

void removeCursor() {                                               //Ŀ��  ������ ����
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}


void processKeyInput() {                                            //Ű �Է� �޴� �޼ҵ�

    /*  ���� Ű �Է��� �ް� �ȴٸ�
    for (int i = 0; i < 20; i++) {
        if (GetAsyncKeyState(VK_LEFT) != 0)    shiftLeft();
        if (GetAsyncKeyState(VK_RIGHT) != 0)   shiftRight();
        if (GetAsyncKeyState(VK_UP) != 0)      rotateBlock();
        if (GetAsyncKeyState(SPACE) != 0)   spaceDown();
        Sleep(g_speed); Sleep(g_speed); Sleep(g_speed); Sleep(g_speed); Sleep(g_speed);
    }
    */
    /*
    int key;
    for (int i = 0; i < 20; i++) {
        if (_kbhit() != 0) {
            key = _getch();
            switch (key) {  //�ҹ��ڰ� �ԷµǾ �����ϰ� �۵��ؾ���
            case 'W': {  jump();    break; }            case 'w': {  jump();    break; }
            case 'A': {  shiftLeft(); break; }          case 'a': {  shiftLeft(); break; }
            case 'D': {  shiftRight(); break; }         case 'd': {  shiftRight(); break; }
            case 'Q': {  shiftDLeft(); break; }         case 'q': {  shiftDLeft(); break; }
            case 'E': {  shiftDRight(); break; }        case 'e': {  shiftDRight(); break; }
            }
        }
        Sleep(g_charSpeed);
    }
    */
    int key;
    if (_kbhit() != 0) {
        key = _getch();
        switch (key) {  //�ҹ��ڰ� �ԷµǾ �����ϰ� �۵��ؾ���
        case 'W': {  jump();    break; }            case 'w': {  jump();    break; }
        case 'A': {  shiftLeft(); break; }          case 'a': {  shiftLeft(); break; }
        case 'D': {  shiftRight(); break; }         case 'd': {  shiftRight(); break; }
        case 'Q': {  shiftDLeft(); break; }         case 'q': {  shiftDLeft(); break; }
        case 'E': {  shiftDRight(); break; }        case 'e': {  shiftDRight(); break; }
        case 'P': {  pushBox(); break; }            case 'p': {  pushBox(); break; }
        }
    }
}

int detectCollision(int posX, int posY) {            // �浹 �˻� �Լ�
//    ��Ʈ���� �Լ���    �浹�ϸ� 0�� ��������
//    ������ ���� �浹, ���ڿ� �浹, NPC�� �浹�� �� �����Ϸ��� �浹 ���� �� 0�� �����ؾ���
                                                                    
//    int arrX = (posX - g_board_origin_x) / 2;
//    int arrY = (posY - g_board_origin_y);
    // ��ǥ�� (0,0)���� �����ؼ� �����̵��� �������� �ʾƵ� ��
    int arrX = posX / 2;
    int arrY = posY    ;
    if (g_curStage == 1) {
//      if (g_stage1GameBoardInfo[arrY][arrX] == 1) return 1;           //���� �浹
//      else if (g_stage1GameBoardInfo[arrY][arrX] == 2) return 1;           //��ֹ��� �浹
//        else if (g_stage1GameBoardInfo[arrY][arrX] == 9) return 9;           //��Ż�� �浹
        return g_stage1GameBoardInfo[arrY][arrX];        
    }
    else if (g_curStage == 2) {
//        if (g_stage2GameBoardInfo[arrY][arrX] == 1) return 1;           //���� �浹
//      else if (g_stage2GameBoardInfo[arrY][arrX] == 2) return 1;           //��ֹ��� �浹
//        else if (g_stage2GameBoardInfo[arrY][arrX] == 9) return 9;           //��Ż�� �浹
        return g_stage2GameBoardInfo[arrY][arrX];
    }
    else {
//        if (g_stage3GameBoardInfo[arrY][arrX] == 1) return 1;           //���� �浹
//      else if (g_stage3GameBoardInfo[arrY][arrX] == 2) return 1;           //��ֹ��� �浹
//        else if (g_stage3GameBoardInfo[arrY][arrX] == 9) return 9;           //��Ż�� �浹
        return g_stage2GameBoardInfo[arrY][arrX];
    }

    //    return 1;
    return 0;
}

int isGameOver() { return g_fatigue >= 100; }    //�Ƿε��� 100�� �̻��̸� 1�� ����

int moveChar(int dx, int dy) {
    COORD curPos = getCurrentCursorPosition();
    int collisionResult = detectCollision(curPos.X + 2 * dx, curPos.Y + dy);
    if (collisionResult == 9) return gotoNextStage();            //���� ��������

    if (g_curStage == 1) {
        g_stage1GameBoardInfo[curPos.Y][curPos.X/2] = 0;
        g_stage1GameBoardInfo[curPos.Y+dy][curPos.X/2 + dx] = 8;
    }
    else if (g_curStage == 2) {
        g_stage2GameBoardInfo[curPos.Y][curPos.X / 2] = 0;
        g_stage2GameBoardInfo[curPos.Y + dy][curPos.X / 2 + dx] = 8;
    }
    else if (g_curStage == 3) {
        g_stage2GameBoardInfo[curPos.Y][curPos.X / 2] = 0;
        g_stage2GameBoardInfo[curPos.Y + dy][curPos.X / 2 + dx] = 8;
    }
    setCurrentCursorPosition(curPos.X + 2 * dx, curPos.Y + dy);

    reDrawMap();
    
}
int shiftLeft() {                                                   // ��
    COORD curPos = getCurrentCursorPosition();
    if(detectCollision(curPos.X - 2, curPos.Y) == 1) return 1;           //���� �ƴϸ� �̵�
                                                
    moveChar(-1, 0);
 
    return 0;
}

int shiftRight() {                                                  // ��
    COORD curPos = getCurrentCursorPosition();
    if (detectCollision(curPos.X + 2, curPos.Y) == 1) return 1;           //���� �ƴϸ� �̵�
   
    moveChar(1, 0);    
    return 0;
}

int jump() {                                                        // ��
    COORD curPos = getCurrentCursorPosition();
    if (detectCollision(curPos.X    , curPos.Y-1) == 1) return 1;           //���� �ƴϸ� �̵�
   
    moveChar(0, -1);                         
//    Sleep(g_charSpeed);
    return 0;

}
int shiftDLeft() {                                                  // ��        �ڡڡ�
    COORD curPos = getCurrentCursorPosition();
    if (detectCollision(curPos.X-2, curPos.Y - 1) == 1) return 1;           //���� �ƴϸ� �̵�

//  moveChar(-1, -1);     �̷��� �Ѵٸ� �ѹ��� �����̵� �� ����    
    moveChar(0 , -1);
                 //���� ���� �밢�� ������ ������.    ->  NPC�� ���� Sleep �ϰ� ��
    moveChar(-1 , 0);
//    Sleep(g_charSpeed);
    
    return 0;
}

int shiftDRight() {                                                  // ��       �ڡڡ�
    COORD curPos = getCurrentCursorPosition();
    if (detectCollision(curPos.X + 2, curPos.Y - 1) == 1) return 1;           //���� �ƴϸ� �̵�

    //moveChar(1, -1);      �̷��� �Ѵٸ� �ѹ��� �����̵� �� ����    
    moveChar(0, -1);
                   //���� ���� �밢�� ������ ������.    ->  NPC�� ���� Sleep �ϰ� ��
    moveChar(1,  0);
//    Sleep(g_gravityAccereralte);

    return 0;
}

int gravity() {                                                      //�߷�           ���� ������ 1 ����
    COORD curPos = getCurrentCursorPosition();
    int collisionResult = detectCollision(curPos.X, curPos.Y + 1);

    if (collisionResult == 0) {

        if (g_curStage == 1) {
            g_stage1GameBoardInfo[curPos.Y][curPos.X/2] = 0;
            g_stage1GameBoardInfo[curPos.Y+1][curPos.X/2] = 8;
        }
        else if (g_curStage == 2) {
            g_stage2GameBoardInfo[curPos.Y][curPos.X/2] = 0;
            g_stage2GameBoardInfo[curPos.Y + 1][curPos.X/2] = 8;
        }
        else if (g_curStage == 3) {
            g_stage3GameBoardInfo[curPos.Y][curPos.X/2] = 0;
            g_stage3GameBoardInfo[curPos.Y + 1][curPos.X/2] = 8;
        }
        setCurrentCursorPosition(curPos.X, curPos.Y+1);
        reDrawMap();
//      Sleep(100);
        return 0;

    }    
    return 1;
}

void initiallize() {                                            // main�Լ� while�� ������ �̸� ���� �Ǿ���ϴ� �Լ���
    
    fullscreen();
    removeCursor();    
    drawStageGameBoardInfo();
    reDrawMap();

//    setCurrentCursorPosition(g_stage1StartPos.X , g_stage1StartPos.Y);
//    printf("��");
    setCurrentCursorPosition(g_stage1StartPos.X, g_stage1StartPos.Y);
}

void drawStageGameBoardInfo() {                                 // ���Ӻ��������� �Է��ϴ� �Լ�
    //�������� �����Ҵ�
    g_stage1GameBoardInfo = malloc(sizeof(int*) * g_stage1Height);
    for (int y = 0; y < g_stage1Height; y++)  g_stage1GameBoardInfo[y] = malloc(sizeof(int) * g_stage1Width); 
    for (int y = 0; y < g_stage1Height; y++)
        for (int x = 0; x < g_stage1Width; x++) g_stage1GameBoardInfo[y][x] = stage1GameBoard[y][x];

    g_stage2GameBoardInfo = malloc(sizeof(int*) * g_stage2Height);
    for (int y = 0; y < g_stage2Height; y++)  g_stage2GameBoardInfo[y] = malloc(sizeof(int) * g_stage2Width); 
    for (int y = 0; y < g_stage2Height; y++)
        for (int x = 0; x < g_stage2Width; x++) g_stage2GameBoardInfo[y][x] = stage2GameBoard[y][x];


    g_stage3GameBoardInfo = malloc(sizeof(int*) * g_stage3Height);
    for (int y = 0; y < g_stage3Height; y++)  g_stage3GameBoardInfo[y] = malloc(sizeof(int) * g_stage3Width); 
    for (int y = 0; y < g_stage3Height; y++)
        for (int x = 0; x < g_stage3Width; x++) g_stage3GameBoardInfo[y][x] = stage3GameBoard[y][x];

}

void reDrawMap() {                                              // �ܼ�â�� �� ������ ������Ʈ
    COORD originPos = getCurrentCursorPosition();   //���� ��ǥ
            
    if (g_curStage == 1) {
        for (int y = 0; y < g_stage1Height; y++) {
            for (int x = 0; x < g_stage1Width; x++) {
                setCurrentCursorPosition(2*x, y);
                if (g_stage1GameBoardInfo[y][x] == 1) printf("��");                      //  ��
                //              else if (g_stage1GameBoardInfo[y][x] == 2) printf("��");     ��ֹ�
                else if (g_stage1GameBoardInfo[y][x] == 8) printf("��");                 //  ĳ����
                else if (g_stage1GameBoardInfo[y][x] == 9) printf("��");                  //  ��Ż                
                else                                   printf("  ");
            }
        }
    }
    else if (g_curStage == 2) {
        for (int y = 0; y < g_stage2Height; y++) {
            for (int x = 0; x < g_stage2Width; x++) {
                setCurrentCursorPosition(2*x, y);
                if (g_stage2GameBoardInfo[y][x] == 1) printf("��");                      //  ��
                //              else if (g_stage2GameBoardInfo[y][x] == 2) printf("��");     ��ֹ�
                else if (g_stage2GameBoardInfo[y][x] == 8) printf("��");                 //  ĳ����
                else if (g_stage2GameBoardInfo[y][x] == 9) printf("��");                  // ��Ż                
                else                                   printf("  ");
            }
        }
    }
    else {
        for (int y = 0; y < g_stage3Height; y++) {
            for (int x = 0; x < g_stage3Width; x++) {
                setCurrentCursorPosition(2*x, y);
                if (g_stage3GameBoardInfo[y][x] == 1) printf("��");                      //  ��
                //              else if (g_stage3GameBoardInfo[y][x] == 2) printf("��");     ��ֹ�
                else if (g_stage3GameBoardInfo[y][x] == 8) printf("��");                 //  ĳ����
                else if (g_stage3GameBoardInfo[y][x] == 9) printf("��");                  // ��Ż                
                else                                   printf("  ");
            }
        }
    }
    setCurrentCursorPosition(originPos.X, originPos.Y);
}
/*
int isNextStage() {
    COORD curPos = getCurrentCursorPosition();
    if      (g_curStage == 1)         if (g_stage1GameBoardInfo[curPos.X][curPos.Y] == 9) gotoNextStage();
    else if (g_curStage == 2)         if (g_stage2GameBoardInfo[curPos.X][curPos.Y] == 9) gotoNextStage();
    else if (g_curStage == 3)         if (g_stage3GameBoardInfo[curPos.X][curPos.Y] == 9) gotoNextStage();
}
*/
int gotoNextStage() {                                                       //���� ���������� �̵�
    g_curStage++;
    reDrawMap();
    if      (g_curStage == 2)   setCurrentCursorPosition(g_stage2StartPos.X, g_stage2StartPos.Y);
    else if (g_curStage == 3)   setCurrentCursorPosition(g_stage3StartPos.X, g_stage3StartPos.Y);
    else if (g_curStage == 4)   victory();
}

void victory() {
    setCurrentCursorPosition(0, 0);
    for (int y = 0; y < g_stage3Height; y++) {
        for (int x = 0; x < g_stage3Width; x++) {
            printf("  ");
        }
        printf(" ");
    }
    setCurrentCursorPosition(30, 10);
    printf("YOU ARE THE WINNER!!");

    setCurrentCursorPosition(0, 30);
    exit(0);
}

void fullscreen() {  SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);} // �ܼ�â ��üȭ��

int gravityBox(int x, int y) {      //�۵��ϸ� 0 ����        �ٲ� y�� ����
    int arrX = x;
    int arrY = y;
    int collisionResult = detectCollision(x, y + 1);

    if (collisionResult == 0) {
        
        if (g_curStage == 1) {
            while (1) {
                if (g_stage1GameBoardInfo[arrY + 1][arrX] == 1)    break;
                g_stage1GameBoardInfo[arrY][arrX] = 0;
                g_stage1GameBoardInfo[arrY + 1][arrX] = 1;
                arrY++;
            }
        }
        else if (g_curStage == 2) {
            while (1) {
                if (g_stage2GameBoardInfo[arrY + 1][arrX] == 1)    break;
                g_stage2GameBoardInfo[arrY][arrX] = 0;
                g_stage2GameBoardInfo[arrY + 1][arrX] = 1;
                arrY++;
            }
        }
        else if (g_curStage == 3) {
            while (1) {
                if (g_stage3GameBoardInfo[arrY + 1][arrX] == 1)    break;
                g_stage3GameBoardInfo[arrY][arrX] = 0;
                g_stage3GameBoardInfo[arrY + 1][arrX] = 1;
                arrY++;
            }
        }
    }
    return 1;
}

void push(int x, int y, int dir) {  // dir : -1 ����  +1 ������               
    //��ǥ�� ������ ��ǥ���ƴ� char�� ��ǥ���� ���
    int arrX = x / 2 + dir; //������ ��ǥ
    int arrY = y;
    if (g_curStage == 1) {
        while (1) {
            if (g_stage1GameBoardInfo[arrY][arrX + dir] == 1) break;
            g_stage1GameBoardInfo[arrY][arrX] = 0;
            g_stage1GameBoardInfo[arrY][arrX + dir] = 1;
            arrX += dir;
            if(gravityBox(arrX, arrY) == 1) break;
        }
    }
    else if (g_curStage == 2) {
        while (1) {
            if (g_stage2GameBoardInfo[arrY][arrX + dir] == 1) break;
            g_stage2GameBoardInfo[arrY][arrX ] = 0;
            g_stage2GameBoardInfo[arrY][arrX + dir] = 1;
            arrX += dir;
            if (gravityBox(arrX, arrY) == 1) break;
        }
    }
    else if (g_curStage == 3) {
        while (1) {
            if (g_stage3GameBoardInfo[arrY][arrX + dir] == 1) break;
            g_stage3GameBoardInfo[arrY][arrX] = 0;
            g_stage3GameBoardInfo[arrY][arrX + dir] = 1;
            arrX += dir;
            if (gravityBox(arrX, arrY) == 1) break;
        }
    }    
    reDrawMap();
    Sleep(100);
}
void pushBox() {
    COORD curPos = getCurrentCursorPosition();
    if (g_curStage == 1) {
        if (g_stage1GameBoardInfo[curPos.Y][curPos.X / 2 + 1] == 1)  //ĳ���� �����ʿ� ���ڰ� ������
            push(curPos.X, curPos.Y, 1);  //���������� �б�
        if (g_stage1GameBoardInfo[curPos.Y][curPos.X / 2 - 1] == 1)  //ĳ����   ���ʿ� ���ڰ� ������
            push(curPos.X, curPos.Y, -1);  //�������� �б�
    }
    else if (g_curStage == 2) {
        if (g_stage2GameBoardInfo[curPos.Y][curPos.X / 2 + 1] == 1)  //ĳ���� �����ʿ� ���ڰ� ������
            push(curPos.X, curPos.Y, 1);  //���������� �б�
        if (g_stage2GameBoardInfo[curPos.Y][curPos.X / 2 - 1] == 1)  //ĳ����   ���ʿ� ���ڰ� ������
            push(curPos.X, curPos.Y, -1);  //�������� �б�
    }
    else if (g_curStage == 3) {
        if (g_stage3GameBoardInfo[curPos.Y][curPos.X / 2 + 1] == 1)  //ĳ���� �����ʿ� ���ڰ� ������
            push(curPos.X, curPos.Y, 1);  //���������� �б�
        if (g_stage3GameBoardInfo[curPos.Y][curPos.X / 2 - 1] == 1)  //ĳ����   ���ʿ� ���ڰ� ������
            push(curPos.X, curPos.Y, -1);  //�������� �б�
    }
//    reDrawMap();
}