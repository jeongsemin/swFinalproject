#pragma once

#include "stage1Map.h" 
#include "stage2Map.h"
#include "stage3Map.h"
#include <Windows.h>
#include <time.h>   //랜덤 함수 시드 위해서
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
// 커서의 위치 = 캐릭터의 위치

//전역 변수
    //스테이지 너비, 높이           
int g_stage1Width = 70;
int g_stage1Height = 20;
int g_stage2Width = 70;
int g_stage2Height = 30;
int g_stage3Width = 70;
int g_stage3Height = 30;
    //스테이지 시작 좌표
COORD g_stage1StartPos = { 2,19 -1 };       //게임보드 y좌표가 0~19이므로     18에서 시작해야함         
COORD g_stage2StartPos = { 2,29 -1 };
COORD g_stage3StartPos = { 2,29 -1 };

int g_curStage = 1;                 //현재 스테이지
int g_charSpeed = 50;               //캐릭터의 이동속도
int g_npcSpeed = 50;                //NPC의 이동속도
int g_gravityAccereralte = 250;     //중력 가속도        점프(q,w,e)를 했을 때 일정 시간 Show 하게 하는 역할     q,w,e 점프 함수 참조
int g_fatigue = 0;                  //피로도

// 게임보드 변수                   동적할당 대신 그냥 수동으로 변경해주는 것으로 결정.
//int g_stage1GameBoardInfo[30][80];									
//int g_stage2GameBoardInfo[30][80];									
//int g_stage3GameBoardInfo[30][80];									
int** g_stage1GameBoardInfo;
int** g_stage2GameBoardInfo;
int** g_stage3GameBoardInfo;

//함수 선언
void setCurrentCursorPosition(int x, int y);                            // 커서 위치 지정

COORD getCurrentCursorPosition();                                       // 커서 위치 반환

void removeCursor();													// 커서  깜빡임 제거

void processKeyInput();													// 키 입력받는 메소드

int detectCollision(int posX, int posY);				            	// 충돌 검사 함수

void initiallize();                                                     // main함수 while문 이전에 미리 수행 되어야하는 함수들

void fullscreen();                                                      // 콘솔창 전체화면

void drawStageGameBoardInfo();                                          // 게임보드정보를 입력하는 함수

int isGameOver();                                                       // 피로도가 100을 이상이면 1을 리턴

int gravity();                                                          // 중력

void reDrawMap();                                                       // 콘솔창에 맵 정보를 업데이트

int moveChar(int dx, int dy);                                           //캐릭터를 (+dx,+dy)만큼 움직임

int jump();                                                             // ↑

int shiftLeft();                                                        // ←

int shiftRight();                                                       // →

int shiftDLeft();                                                       // ↖       ★★★

int shiftDRight();                                                      // ↗       ★★★

//int isNextStage();                                                      // 포탈과 충돌했는지 점검하는 함수

int gotoNextStage();                                                    // 다음 스테이지로 이동하는 함수

void victory();                                                         // 게임 승리

int gravityBox(int x, int y);                                           // 박스에 중력을 적용시키는 함수

void pushBox();                                                         // 박스 밀기 함수(조건체크)

void push(int x, int y, int dir);                                       // 박스를 미는 함수(구현)
//함수 구현

void fatigue()
{
    COORD curPos = getCurrentCursorPosition();
    
    setCurrentCursorPosition(20, 0);
    printf("피로도 : %d",g_fatigue);
    setCurrentCursorPosition(curPos.X, curPos.Y);

}
void setCurrentCursorPosition(int x, int y) {                           //커서 위치 지정
    COORD p = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

COORD getCurrentCursorPosition() {                                      //커서 위치 반환
    CONSOLE_SCREEN_BUFFER_INFO curInfo;
    COORD out;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    out.X = curInfo.dwCursorPosition.X;
    out.Y = curInfo.dwCursorPosition.Y;
    return out;
}

void removeCursor() {                                               //커서  깜빡임 제거
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}


void processKeyInput() {                                            //키 입력 받는 메소드

    /*  다중 키 입력을 받게 된다면
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
            switch (key) {  //소문자가 입력되어도 동일하게 작동해야함
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
        switch (key) {  //소문자가 입력되어도 동일하게 작동해야함
        case 'W': {  jump();    break; }            case 'w': {  jump();    break; }
        case 'A': {  shiftLeft(); break; }          case 'a': {  shiftLeft(); break; }
        case 'D': {  shiftRight(); break; }         case 'd': {  shiftRight(); break; }
        case 'Q': {  shiftDLeft(); break; }         case 'q': {  shiftDLeft(); break; }
        case 'E': {  shiftDRight(); break; }        case 'e': {  shiftDRight(); break; }
        case 'P': {  pushBox(); break; }            case 'p': {  pushBox(); break; }
        }
    }
}

int detectCollision(int posX, int posY) {            // 충돌 검사 함수
//    테트리스 함수는    충돌하면 0을 리턴했음
//    하지만 벽과 충돌, 지뢰와 충돌, NPC와 충돌을 다 생각하려면 충돌 안할 때 0을 리턴해야함
                                                                    
//    int arrX = (posX - g_board_origin_x) / 2;
//    int arrY = (posY - g_board_origin_y);
    // 좌표가 (0,0)에서 시작해서 평행이동은 생각하지 않아도 됨
    int arrX = posX / 2;
    int arrY = posY    ;
    if (g_curStage == 1) {
//      if (g_stage1GameBoardInfo[arrY][arrX] == 1) return 1;           //벽과 충돌
//      else if (g_stage1GameBoardInfo[arrY][arrX] == 2) return 1;           //장애물과 충돌
//        else if (g_stage1GameBoardInfo[arrY][arrX] == 9) return 9;           //포탈과 충돌
        return g_stage1GameBoardInfo[arrY][arrX];        
    }
    else if (g_curStage == 2) {
//        if (g_stage2GameBoardInfo[arrY][arrX] == 1) return 1;           //벽과 충돌
//      else if (g_stage2GameBoardInfo[arrY][arrX] == 2) return 1;           //장애물과 충돌
//        else if (g_stage2GameBoardInfo[arrY][arrX] == 9) return 9;           //포탈과 충돌
        return g_stage2GameBoardInfo[arrY][arrX];
    }
    else {
//        if (g_stage3GameBoardInfo[arrY][arrX] == 1) return 1;           //벽과 충돌
//      else if (g_stage3GameBoardInfo[arrY][arrX] == 2) return 1;           //장애물과 충돌
//        else if (g_stage3GameBoardInfo[arrY][arrX] == 9) return 9;           //포탈과 충돌
        return g_stage2GameBoardInfo[arrY][arrX];
    }

    //    return 1;
    return 0;
}

int isGameOver() { return g_fatigue >= 100; }    //피로도가 100을 이상이면 1을 리턴

int moveChar(int dx, int dy) {
    COORD curPos = getCurrentCursorPosition();
    int collisionResult = detectCollision(curPos.X + 2 * dx, curPos.Y + dy);
    if (collisionResult == 9) return gotoNextStage();            //다음 스테이지

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
int shiftLeft() {                                                   // ←
    COORD curPos = getCurrentCursorPosition();
    if(detectCollision(curPos.X - 2, curPos.Y) == 1) return 1;           //벽만 아니면 이동
                                                
    moveChar(-1, 0);
 
    return 0;
}

int shiftRight() {                                                  // →
    COORD curPos = getCurrentCursorPosition();
    if (detectCollision(curPos.X + 2, curPos.Y) == 1) return 1;           //벽만 아니면 이동
   
    moveChar(1, 0);    
    return 0;
}

int jump() {                                                        // ↑
    COORD curPos = getCurrentCursorPosition();
    if (detectCollision(curPos.X    , curPos.Y-1) == 1) return 1;           //벽만 아니면 이동
   
    moveChar(0, -1);                         
//    Sleep(g_charSpeed);
    return 0;

}
int shiftDLeft() {                                                  // ↖        ★★★
    COORD curPos = getCurrentCursorPosition();
    if (detectCollision(curPos.X-2, curPos.Y - 1) == 1) return 1;           //벽만 아니면 이동

//  moveChar(-1, -1);     이렇게 한다면 한번에 순간이동 할 것임    
    moveChar(0 , -1);
                 //내가 말한 대각선 점프의 문제점.    ->  NPC도 같이 Sleep 하게 됨
    moveChar(-1 , 0);
//    Sleep(g_charSpeed);
    
    return 0;
}

int shiftDRight() {                                                  // ↗       ★★★
    COORD curPos = getCurrentCursorPosition();
    if (detectCollision(curPos.X + 2, curPos.Y - 1) == 1) return 1;           //벽만 아니면 이동

    //moveChar(1, -1);      이렇게 한다면 한번에 순간이동 할 것임    
    moveChar(0, -1);
                   //내가 말한 대각선 점프의 문제점.    ->  NPC도 같이 Sleep 하게 됨
    moveChar(1,  0);
//    Sleep(g_gravityAccereralte);

    return 0;
}

int gravity() {                                                      //중력           땅에 닿으면 1 리턴
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

void initiallize() {                                            // main함수 while문 이전에 미리 수행 되어야하는 함수들
    
    fullscreen();
    removeCursor();    
    drawStageGameBoardInfo();
    reDrawMap();

//    setCurrentCursorPosition(g_stage1StartPos.X , g_stage1StartPos.Y);
//    printf("◎");
    setCurrentCursorPosition(g_stage1StartPos.X, g_stage1StartPos.Y);
}

void drawStageGameBoardInfo() {                                 // 게임보드정보를 입력하는 함수
    //스테이지 동적할당
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

void reDrawMap() {                                              // 콘솔창에 맵 정보를 업데이트
    COORD originPos = getCurrentCursorPosition();   //원래 좌표
            
    if (g_curStage == 1) {
        for (int y = 0; y < g_stage1Height; y++) {
            for (int x = 0; x < g_stage1Width; x++) {
                setCurrentCursorPosition(2*x, y);
                if (g_stage1GameBoardInfo[y][x] == 1) printf("▩");                      //  벽
                //              else if (g_stage1GameBoardInfo[y][x] == 2) printf("♨");     장애물
                else if (g_stage1GameBoardInfo[y][x] == 8) printf("◎");                 //  캐릭터
                else if (g_stage1GameBoardInfo[y][x] == 9) printf("Ж");                  //  포탈                
                else                                   printf("  ");
            }
        }
    }
    else if (g_curStage == 2) {
        for (int y = 0; y < g_stage2Height; y++) {
            for (int x = 0; x < g_stage2Width; x++) {
                setCurrentCursorPosition(2*x, y);
                if (g_stage2GameBoardInfo[y][x] == 1) printf("▩");                      //  벽
                //              else if (g_stage2GameBoardInfo[y][x] == 2) printf("♨");     장애물
                else if (g_stage2GameBoardInfo[y][x] == 8) printf("◎");                 //  캐릭터
                else if (g_stage2GameBoardInfo[y][x] == 9) printf("Ж");                  // 포탈                
                else                                   printf("  ");
            }
        }
    }
    else {
        for (int y = 0; y < g_stage3Height; y++) {
            for (int x = 0; x < g_stage3Width; x++) {
                setCurrentCursorPosition(2*x, y);
                if (g_stage3GameBoardInfo[y][x] == 1) printf("▩");                      //  벽
                //              else if (g_stage3GameBoardInfo[y][x] == 2) printf("♨");     장애물
                else if (g_stage3GameBoardInfo[y][x] == 8) printf("◎");                 //  캐릭터
                else if (g_stage3GameBoardInfo[y][x] == 9) printf("Ж");                  // 포탈                
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
int gotoNextStage() {                                                       //다음 스테이지로 이동
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

void fullscreen() {  SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);} // 콘솔창 전체화면

int gravityBox(int x, int y) {      //작동하면 0 리턴        바뀐 y값 리턴
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

void push(int x, int y, int dir) {  // dir : -1 왼쪽  +1 오른쪽               
    //좌표가 상자의 좌표가아닌 char의 좌표임을 명심
    int arrX = x / 2 + dir; //상자의 좌표
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
        if (g_stage1GameBoardInfo[curPos.Y][curPos.X / 2 + 1] == 1)  //캐릭터 오른쪽에 상자가 있으면
            push(curPos.X, curPos.Y, 1);  //오른쪽으로 밀기
        if (g_stage1GameBoardInfo[curPos.Y][curPos.X / 2 - 1] == 1)  //캐릭터   왼쪽에 상자가 있으면
            push(curPos.X, curPos.Y, -1);  //왼쪽으로 밀기
    }
    else if (g_curStage == 2) {
        if (g_stage2GameBoardInfo[curPos.Y][curPos.X / 2 + 1] == 1)  //캐릭터 오른쪽에 상자가 있으면
            push(curPos.X, curPos.Y, 1);  //오른쪽으로 밀기
        if (g_stage2GameBoardInfo[curPos.Y][curPos.X / 2 - 1] == 1)  //캐릭터   왼쪽에 상자가 있으면
            push(curPos.X, curPos.Y, -1);  //왼쪽으로 밀기
    }
    else if (g_curStage == 3) {
        if (g_stage3GameBoardInfo[curPos.Y][curPos.X / 2 + 1] == 1)  //캐릭터 오른쪽에 상자가 있으면
            push(curPos.X, curPos.Y, 1);  //오른쪽으로 밀기
        if (g_stage3GameBoardInfo[curPos.Y][curPos.X / 2 - 1] == 1)  //캐릭터   왼쪽에 상자가 있으면
            push(curPos.X, curPos.Y, -1);  //왼쪽으로 밀기
    }
//    reDrawMap();
}