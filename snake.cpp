//main.c
//snake
//
//Created by ZiHao Mao on 15-12-26
//Copyright (c) 2015�� Sun Yat-sen University. All rights reserved 
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
#define SLEEPTIME 150         /*������ԸĶ�sleep�����ƶ����ʱ�䣬�Ӷ����Ե�����Ϸ�Ѷ�*/ 

//snake stepping: dy = -1(up), 1(down); dx = -1(left), 1(right), 0(no move)
void snakemove(void);
//put a food randomized on a blank cell
void put_money(void);
//out cells of the grid
void output(void);
//outs when gameover
void gameover(void);

char map[13][13]=       /*û���ߵ�ͼ*/ 
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
    {"************",         /*��ʼͼ*/
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
    "* A        *",          /*gameover�����ʾ��ͼ*/ 
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

void put_money(void) {                            /*ͨ��һ�������ʱ�����Ӳ���ÿ�β�ͬ��α������������������1-10��Ϊʳ�������*/
    int foodx, foody;
    foodx = rand() % 10 + 1;
    foody = rand() % 10 + 1;
    if (map[foodx][foody] != 'H'||'X'||'*') {      /*ʳ����������������Ƶ�*/ 
        map[foodx][foody] = '$';
    } else{
        put_money();
    }
}

void gameover(void) {
    int i, j;
    system("cls");
    for (i = 0; i < 13; i++) {                        /*�����ڽ���gameover��������ӡgameover��Ӧ��ͼ��ͬʱ�������*/ 
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
        if (kbhit()) {                   /*����ͨ��kbhit��getchʹ������û��ת��ʱ���Զ���ǰ����*/
            input = getch();
        } else {
        if (foodflag) {                     /*��ͼ��û��ʳ���ʱ������ʳ��*/
            put_money();
            foodflag = 0;
        }
        switch (input) {
            case 'w':
                if (map[snakeX[snakelength - 1]][snakeY[snakelength - 1] - 1] == '$') {
                    snakelength++;
                    snakeY[snakelength - 1] = snakeY[snakelength - 2] - 1;
                    snakeX[snakelength - 1] = snakeX[snakelength - 2];                           /*W��Ӧ�Ķ�����if�ж�Ӧ���ǳ�ʳ�������Ķ���*/
                    map[snakeX[snakelength - 1]][snakeY[snakelength - 1]] = 'H';                       
                    map[snakeX[snakelength - 2]][snakeY[snakelength - 2]] = 'X';
                    foodflag = 1;
                } else if (map[snakeX[snakelength - 1]][snakeY[snakelength - 1] - 1] == 'X'||map[snakeX[snakelength - 1]][snakeY[snakelength - 1] - 1] == '*'){
                    gameover();                                                                   /*else if��Ӧ���ǻ����gameover�Ķ�����ײǽ��*/
                } else {
                map[snakeX[0]][snakeY[0]] = ' ';
                for (i = 0; i < snakelength - 1; i++) {
                    snakeX[i] = snakeX[i + 1];                                           /*ʣ�µ����������ƶ��Ķ���*/
                    snakeY[i] = snakeY[i + 1];
                    map[snakeX[i]][snakeY[i]] = 'X';
                    }
                snakeY[snakelength - 1] -= 1;
                map[snakeX[snakelength - 1]][snakeY[snakelength - 1]] = 'H';
                }
                break;
                
            case 'a':
                if (map[snakeX[snakelength - 1] - 1][snakeY[snakelength - 1]] == '$') {             /*��Wͬ��*/
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
                if (map[snakeX[snakelength - 1]][snakeY[snakelength - 1] + 1] == '$'){                    /*��Wͬ��*/
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
                    snakelength++;                                                                    /*��Wͬ��*/
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
        if (snakelength > 21) {                                                        /*�߳���20����Ϸ�ͻ����*/ 
            gameover();
        }
        Sleep(SLEEPTIME);                                                               /*sleep�������Զ����ߵ�����ʱ����������һ���ӳ���ͬʱ������Ϸ�Ѷ�*/
        if (GameOverFlag) {
        system("cls");
        for (i = 0; i < 13; i++) {                                                 /*ÿ����·�����������Ҵ�ӡ��ǰ��λ��*/
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
    int i, j, k, input;                                        /*����WASD��һ������ʼ��Ϸ*/
    snakemove();
    return 0;
}

