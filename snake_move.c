#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>

#define SNAKE_MAX_LENGTH 20 //蛇的最大长度
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define SNAKE_FOOD '$'
#define WALL_CELL '*'

int snakeX[SNAKE_MAX_LENGTH] = {1,1,1,1,1}; //x轴坐标
int snakeY[SNAKE_MAX_LENGTH] = {1,2,3,4,5}; //y轴坐标
int snakeLength = 5; //蛇的现长

int snakeMove(char move);
void output();
void gamestart();

char map[12][12]=
   {"************",
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

int snakeMove(char move){
    switch(move){
        case 'W'://往上
            //判断移动方向是否与先前移动方向相反，则不作方向调整
            if(snakeX[snakeLength-1] == snakeX[snakeLength-2]+1 
            && snakeY[snakeLength-1] == snakeY[snakeLength-2]){
                return -1;
            }
            //先移动身体
            map[snakeX[0]][snakeY[0]] = BLANK_CELL;
            for(int i = 0;i < snakeLength-1;i++){
                snakeX[i] = snakeX[i+1];
                snakeY[i] = snakeY[i+1];
                map[snakeX[i]][snakeY[i]] = SNAKE_BODY;
            }
            //判断头是否撞到墙
            if(map[snakeX[snakeLength-1]-1][snakeY[snakeLength-1]] == WALL_CELL){
                return 0;
            }
            //判断头是否与移动后的身体相撞
            if(map[snakeX[snakeLength-1]-1][snakeY[snakeLength-1]] == SNAKE_BODY){
                return 0;
            }
            else{
                snakeX[snakeLength-1] = snakeX[snakeLength-1]-1;
                map[snakeX[snakeLength-1]][snakeY[snakeLength-1]] = SNAKE_HEAD;
                return 1;
            }
            break;
        //以下与向上操作同理
        case 'S':
            if(snakeX[snakeLength-1] == snakeX[snakeLength-2]-1 
            && snakeY[snakeLength-1] == snakeY[snakeLength-2]){
                return -1;
            }
            map[snakeX[0]][snakeY[0]] = BLANK_CELL;
            for(int i = 0;i < snakeLength-1;i++){
                snakeX[i] = snakeX[i+1];
                snakeY[i] = snakeY[i+1];
                map[snakeX[i]][snakeY[i]] = SNAKE_BODY;
            }
            if(map[snakeX[snakeLength-1]+1][snakeY[snakeLength-1]] == WALL_CELL){
                return 0;
            }
            if(map[snakeX[snakeLength-1]+1][snakeY[snakeLength-1]] == SNAKE_BODY){
                return 0;
            }
            else{
                snakeX[snakeLength-1] = snakeX[snakeLength-1]+1;
                map[snakeX[snakeLength-1]][snakeY[snakeLength-1]] = SNAKE_HEAD;
                return 1;
            }
            break;
        case 'A':
            if(snakeX[snakeLength-1] == snakeX[snakeLength-2] 
            && snakeY[snakeLength-1] == snakeY[snakeLength-2]+1){
                return -1;
            }
            map[snakeX[0]][snakeY[0]] = BLANK_CELL;
            for(int i = 0;i < snakeLength-1;i++){
                snakeX[i] = snakeX[i+1];
                snakeY[i] = snakeY[i+1];
                map[snakeX[i]][snakeY[i]] = SNAKE_BODY;
            }
            if(map[snakeX[snakeLength-1]][snakeY[snakeLength-1]-1] == WALL_CELL){
                return 0;
            }
            if(map[snakeX[snakeLength-1]][snakeY[snakeLength-1]-1] == SNAKE_BODY){
                return 0;
            }
            else{
                snakeY[snakeLength-1] = snakeY[snakeLength-1]-1;
                map[snakeX[snakeLength-1]][snakeY[snakeLength-1]] = SNAKE_HEAD;
                return 1;
            }
            break;
        case 'D':
            if(snakeX[snakeLength-1] == snakeX[snakeLength-2] 
            && snakeY[snakeLength-1] == snakeY[snakeLength-2]-1){
                return -1;
            }
            map[snakeX[0]][snakeY[0]] = BLANK_CELL;
            for(int i = 0;i < snakeLength-1;i++){
                snakeX[i] = snakeX[i+1];
                snakeY[i] = snakeY[i+1];
                map[snakeX[i]][snakeY[i]] = SNAKE_BODY;
            }
            if(map[snakeX[snakeLength-1]][snakeY[snakeLength-1]+1] == WALL_CELL){
                return 0;
            }
            if(map[snakeX[snakeLength-1]][snakeY[snakeLength-1]+1] == SNAKE_BODY){
                return 0;
            }
            else{
                snakeY[snakeLength-1] = snakeY[snakeLength-1]+1;
                map[snakeX[snakeLength-1]][snakeY[snakeLength-1]] = SNAKE_HEAD;
                return 1;
            }
            break;
        //输入不为AWSD时，会保持原有的方向移动
        default:
            //return -1;
            break;
    }
}

void output(){  //输出地图
    printf("======================\n");
    for(int i = 0;i < 12;i++){
        printf("     ");
        for(int j = 0;j < 12;j++){
            printf("%c",map[i][j]);
        }
        printf("\n");
    }
    Sleep(1000);//控制蛇的速度
}

void gamestart(){
    char move = 'D'; //初始为向右出发
    char tmp;
    output();
    while(1){
        scanf("%c",&move);
        int start = snakeMove(move);
        if(start == 1){
            tmp = move;  //tmp保存先前移动方向
            output();
        }
        if(start == -1){  //-1代表这次输入与蛇先前移动方向相反，所以不改变移动方向
            start = snakeMove(tmp);
            output();
        }
        if(start == 0){
            output();
            printf("撞到了墙或者身体，你已死亡\n");
            break;
        }
    }
}

int main(){
    gamestart();
    return 0;
}