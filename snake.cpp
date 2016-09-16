//main.c
//snake
//
//Created by ZiHao Mao on 15-12-26
//Copyright (c) 2015年 Sun Yat-sen University. All rights reserved 
//

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

#define SNAKE_MAX_LENGTH 20
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define SNAKE_food '$'
#define WALL_CELL '*'
#define SLEEPTIME 150         /*在这可以改动sleep函数移动间隔时间，从而可以调整游戏难度*/ 

//snake stepping: dy = -1(up), 1(down); dx = -1(left), 1(right), 0(no move)
void snakemove(void);
//put a food randomized on a blank cell
void put_money(void);
//out cells of the grid
void output(void);
//outs when gameover
void gameover(void);

char map[13][13]=       /*没有蛇的图*/ 
    {"************",
    "*          *",
    "*          *",
    "*          *",
    "*          *",
    "*          *",
    "*          *",
    "*          *",
    "*          *",
    "*          *",
    "*          *",
    "************"};
char startmap[13][13]=
    {"************",         /*开始图*/
    "*XXXXH     *",
    "*          *",
    "*          *",
    "*          *",
    "*          *",
    "*          *",
    "*          *",
    "*          *",
    "*          *",
    "*          *",
    "************"};

char gameovermap[13][13]=
    {"************",
    "*G         *",
    "* A        *",          /*gameover后会显示的图*/ 
    "*  M       *",
    "*   E      *",
    "*    O     *",
    "*     V    *",
    "*      E   *",
    "*       R  *",
    "*        ! *",
    "*          *",
    "************"};

int snakeX[SNAKE_MAX_LENGTH]={1, 2, 3, 4, 5};
int snakeY[SNAKE_MAX_LENGTH]={1, 1, 1, 1, 1};
int snakelength = 5;
int GameOverFlag = 1;
int foodflag = 1;

void put_money(void) {                            /*通过一个随机的时间种子产生每次不同的伪随机数（像真随机数）1-10作为食物的坐标*/
    int foodx, foody;
    foodx = rand() % 10 + 1;
    foody = rand() % 10 + 1;
    if (map[foodx][foody] != 'H'||'X'||'*') {      /*食物坐标出现是有限制的*/ 
        map[foodx][foody] = '$';
    } else{
        put_money();
    }
}

void gameover(void) {
    int i, j;
    system("cls");
    for (i = 0; i < 13; i++) {                        /*这里在进入gameover函数后会打印gameover对应的图案同时程序结束*/ 
        for (j = 0; j < 13; j++) {
            printf("%c", gameovermap[i][j]);
        }
        printf("\n");
    }
    GameOverFlag = 0;
}

void snakemove(void) {
        int i, j, input, direction;
        while (GameOverFlag) {
        if (kbhit()) {                   /*这里通过kbhit和getch使得蛇在没有转向时会自动向前行走*/
            input = getch();
        } else {
        if (foodflag) {                     /*在图上没有食物的时候会放置食物*/
            put_money();
            foodflag = 0;
        }
        switch (input) {
            case 'w':
                if (map[snakeX[snakelength - 1]][snakeY[snakelength - 1] - 1] == '$') {
                    snakelength++;
                    snakeY[snakelength - 1] = snakeY[snakelength - 2] - 1;
                    snakeX[snakelength - 1] = snakeX[snakelength - 2];                           /*W对应的动作，if中对应的是吃食物增长的动作*/
                    map[snakeX[snakelength - 1]][snakeY[snakelength - 1]] = 'H';                       
                    map[snakeX[snakelength - 2]][snakeY[snakelength - 2]] = 'X';
                    foodflag = 1;
                } else if (map[snakeX[snakelength - 1]][snakeY[snakelength - 1] - 1] == 'X'||map[snakeX[snakelength - 1]][snakeY[snakelength - 1] - 1] == '*'){
                    gameover();                                                                   /*else if对应的是会产生gameover的动作如撞墙等*/
                } else {
                map[snakeX[0]][snakeY[0]] = ' ';
                for (i = 0; i < snakelength - 1; i++) {
                    snakeX[i] = snakeX[i + 1];                                           /*剩下的则是正常移动的动作*/
                    snakeY[i] = snakeY[i + 1];
                    map[snakeX[i]][snakeY[i]] = 'X';
                    }
                snakeY[snakelength - 1] -= 1;
                map[snakeX[snakelength - 1]][snakeY[snakelength - 1]] = 'H';
                }
                break;
                
            case 'a':
                if (map[snakeX[snakelength - 1] - 1][snakeY[snakelength - 1]] == '$') {             /*与W同理*/
                    snakelength++;
                    snakeX[snakelength - 1] = snakeX[snakelength - 2] - 1;
                    snakeY[snakelength - 1] = snakeY[snakelength - 2];
                    map[snakeX[snakelength - 1]][snakeY[snakelength - 1]] = 'H';
                    map[snakeX[snakelength - 2]][snakeY[snakelength - 2]] = 'X';
                foodflag = 1;
                } else if (map[snakeX[snakelength - 1] - 1][snakeY[snakelength - 1]] == 'X'||map[snakeX[snakelength - 1] - 1][snakeY[snakelength - 1]] == '*') {
                    gameover();
                }
                else {
                map[snakeX[0]][snakeY[0]] = ' ';
                for (i = 0; i < snakelength - 1; i++) {
                    snakeX[i] = snakeX[i + 1];
                    snakeY[i] = snakeY[i + 1];
                    map[snakeX[i]][snakeY[i]] = 'X';
                }
                snakeX[snakelength - 1] -= 1;
                map[snakeX[snakelength - 1]][snakeY[snakelength - 1]] = 'H';
                }
                break;
                
            case 's':
                if (map[snakeX[snakelength - 1]][snakeY[snakelength - 1] + 1] == '$'){                    /*与W同理*/
                    snakelength++;
                    snakeY[snakelength - 1] = snakeY[snakelength - 2] + 1;
                    snakeX[snakelength - 1] = snakeX[snakelength - 2];
                    map[snakeX[snakelength - 1]][snakeY[snakelength - 1]] = 'H';
                    map[snakeX[snakelength - 2]][snakeY[snakelength - 2]] = 'X';
                foodflag = 1;
                } else if (map[snakeX[snakelength - 1]][snakeY[snakelength - 1] + 1] == 'X'||map[snakeX[snakelength - 1]][snakeY[snakelength - 1] + 1] == '*') {
                gameover();
                }
                else {
                map[snakeX[0]][snakeY[0]] = ' ';    
                for (i = 0; i < snakelength - 1; i++) {
                    snakeX[i] = snakeX[i + 1];
                    snakeY[i] = snakeY[i + 1];
                    map[snakeX[i]][snakeY[i]] = 'X';
                }
                snakeY[snakelength - 1] += 1;
                map[snakeX[snakelength - 1]][snakeY[snakelength - 1]] = 'H';
                }
                break;
                
            case 'd':
                if (map[snakeX[snakelength - 1] + 1][snakeY[snakelength - 1]] == '$') {
                    snakelength++;                                                                    /*与W同理*/
                    snakeX[snakelength - 1] = snakeX[snakelength - 2] + 1;
                    snakeY[snakelength - 1] = snakeY[snakelength - 2];
                    map[snakeX[snakelength - 1]][snakeY[snakelength - 1]] = 'H';
                    map[snakeX[snakelength - 2]][snakeY[snakelength - 2]] = 'X';
                foodflag = 1;
                } else if (map[snakeX[snakelength - 1] + 1][snakeY[snakelength - 1]] == 'X'||map[snakeX[snakelength - 1] + 1][snakeY[snakelength - 1]] == '*') {
                    gameover();
                } 
                else {
                map[snakeX[0]][snakeY[0]] = ' ';  
                for (i = 0; i < snakelength - 1; i++) {
                    snakeX[i] = snakeX[i + 1];
                    snakeY[i] = snakeY[i + 1];
                    map[snakeX[i]][snakeY[i]] = 'X';
                }
                snakeX[snakelength - 1] += 1;
                map[snakeX[snakelength - 1]][snakeY[snakelength - 1]] = 'H';
                }
                break;
        }
        if (snakelength > 21) {                                                        /*蛇超过20节游戏就会结束*/ 
            gameover();
        }
        Sleep(SLEEPTIME);                                                               /*sleep函数让自动行走的蛇有时间间隔，不会一下子出格，同时调整游戏难度*/
        if (GameOverFlag) {
        system("cls");
        for (i = 0; i < 13; i++) {                                                 /*每次走路都会清屏并且打印当前的位置*/
        for (j = 0; j < 13; j++) {
            printf("%c", map[j][i]);
        }
        printf("\n");
    }
}
}
}
}

int main(void) {
    int i, j, k, input;                                        /*按下WASD任一按键开始游戏*/
    snakemove();
    return 0;
}

