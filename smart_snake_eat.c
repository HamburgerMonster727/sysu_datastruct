#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include <math.h>

#define SNAKE_MAX_LENGTH 20 //蛇的最大长度
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define SNAKE_FOOD '$'
#define WALL_CELL '*'

int snakeX[SNAKE_MAX_LENGTH] = {1,1,1,1,1}; //x轴坐标
int snakeY[SNAKE_MAX_LENGTH] = {1,2,3,4,5}; //y轴坐标
int snakeLength = 5; //蛇的现长
int foodX; //食物的x坐标
int foodY; //食物的y坐标
int tmpX;  //先前的x坐标
int tmpY;  //先前的y坐标
int point = 0;//得分
int eatfood = 0; //判断是否吃掉了食物
char move[30]; //保存生成路径的move
int step; //用于遍历move
int stepnum; //记录当前路径有多少步

void creatfood();
void output();
void gamestart();
int snakeMove(int x,int y);
int is_wrongway(int x,int y);
int is_eatfood(int x,int y);
int is_hitbody(int x,int y);
int is_hitwall(int x,int y);
void movehead(int x,int y);
void movebody();
int smartMove();
int is_over();

char map[12][12]=
   {"************",
    "*XXXXH     *",
    "*          *",
    "*          *",
    "*          *",
    "*          *",
    "*          *",
    "*   ****   *",
    "*          *",
    "*          *",
    "*          *",
    "************"};

void gamestart(){
    creatfood();
    stepnum = smartMove();//生成初始路径
    output();
    while(1){
        if(eatfood == 1){ //吃到了食物，生成新的路径
            stepnum = smartMove(); 
            eatfood = 0;
        }
        int start;
        int over = 0;
        for(step = 0;step <= stepnum;step++){ //遍历move
            switch(move[step]){
                case 'W':
                    start = snakeMove(-1,0);             
                    break;
                case 'S':
                    start = snakeMove(1,0);              
                    break;
                case 'A':
                    start = snakeMove(0,-1);            
                    break;
                case 'D':
                    start = snakeMove(0,1);
                    break;
                default:  //输入错误保持先前的方向移动
                    start = snakeMove(tmpX,tmpY);
                    break;
            }
            if(start == 1){
                output();
            }
            if(start == 0){
                over = 1;
                output();
                printf("撞到了墙或者身体，你已死亡\n");
                break;
            }
        }
        if(over == 1)
            break;
    }
}

int smartMove(){ //生成路径
    int distanceX = foodX - snakeX[snakeLength-1];
    int distanceY = foodY - snakeY[snakeLength-1];
    int i = 0;
    for(int j = 1;j <= abs(distanceX);j++){
        if(distanceX > 0)
            move[i] = 'S';
        else
            move[i] = 'W';
        i++;
    }
    for(int j = 1;j <= abs(distanceY);j++){
        if(distanceY > 0)
            move[i] = 'D';
        else
            move[i] = 'A';
        i++;
    }
    return i-1;
}

int snakeMove(int x,int y){
    //判断是否已被四周围死
    if(is_over()){
        return 0;
    }
    //判断移动方向是否与先前移动方向相反，则不作方向调整
    if(is_wrongway(x,y)){
        return snakeMove(tmpX,tmpY);
    }
    //判断头是否吃到食物,若吃到,不用移动身体只需把食物变为头部即可
    if(is_eatfood(x,y)){
        tmpX = x,tmpY = y;
        eatfood = 1;
        return 1;
    }
    else{
        //判断头是否撞到墙
        if(is_hitwall(x,y)){ //撞到了墙，要调整方向继续前进
            int flag1 = is_hitwall(y,x);
            int flag2 = is_hitwall(-y,-x);
            int flag3 = is_hitbody(y,x);
            int flag4 = is_hitbody(-y,-x);
            int flag5 = is_hitbody(-x,-y);
            if(flag1 == 1 && flag2 == 1){//左右都为墙
                return 0;
            }
            if(flag1 == 1 && flag2 != 1){//左边为墙
                if(flag4 != 1)
                    snakeMove(-y,-x);
                else //左墙右身体，无法调整方向
                    return 0;
                output();
            }
            if(flag2 == 1 && flag1 != 1){//右边为墙
                if(flag3 != 1)
                    snakeMove(y,x);
                else //右墙左身体，无法调整方向
                    return 0;
                output();
            }
            if(flag1 != 1 && flag2 != 1){ //左右无墙，主要判断身体
                if(flag3 == 1 && flag4 == 1){//左右都为身体
                    if(flag5 != 1){
                        snakeMove(-x,-y);
                        output();
                    }
                    else
                        return 0;
                }
                if(flag3 == 1 && flag4 != 1){//左边为身体
                    snakeMove(-y,-x);
                    output();
                }
                if(flag4 == 1 && flag3 != 1){//右边为身体
                    snakeMove(y,x);
                    output();
                }
                if(flag3 != 1 && flag4 != 1){//左右都无身体
                    snakeMove(y,x);//随便选一个方向前进
                    output();
                }
            }
            stepnum = smartMove(move);
            step = 0;
            return 1;
        }
        //判断头是否与移动后的身体相撞
        if(is_hitbody(x,y)){//撞到了身体，要调整方向
            int flag1 = is_hitbody(y,x);
            int flag2 = is_hitbody(-y,-x);
            int flag3 = is_hitbody(-x,-y);
            if(flag1 == 1 && flag2 == 1){//左右都为身体
                if(flag3 != 1){//后不为身体
                    snakeMove(-x,-y);
                    output;
                }
                else
                    return 0;
            }
            if(flag1 == 1 && flag2 != 1){//左为身体
                snakeMove(-y,-x);
                output();
            }
            if(flag2 == 1 && flag1 != 1){//右为身体
                snakeMove(y,x);
                output();
            }
            if(flag1 != 1 && flag2 != 1){//左右都无身体
                snakeMove(y,x); //随便选一个方向前进
                output();
            }
            stepnum = smartMove(move);
            step = 0;
            return 1;
        }
        else{
            movebody();
            movehead(x,y);
            tmpX = x,tmpY = y;
            return 1;
        }
    }
}

int is_over(){
    int x = 1,y = 0;
    int w = is_hitbody(x,y)+is_hitwall(x,y);
    int s = is_hitbody(-x,-y)+is_hitwall(-x,-y);
    int a = is_hitbody(y,x)+is_hitwall(y,x);
    int d = is_hitbody(-y,-x)+is_hitwall(-y,-x);
    if(w > 0 && s > 0 && a > 0 && d > 0)
        return 1;
    return 0;
}

int is_wrongway(int x,int y){
    if(snakeX[snakeLength-1]+x == snakeX[snakeLength-2] && snakeY[snakeLength-1]+y == snakeY[snakeLength-2])
        return 1;
    return 0;
}

int is_eatfood(int x,int y){
    if(map[snakeX[snakeLength-1]+x][snakeY[snakeLength-1]+y] == SNAKE_FOOD){
        if(snakeLength < SNAKE_MAX_LENGTH){
            map[snakeX[snakeLength-1]][snakeY[snakeLength-1]] = SNAKE_BODY;
            snakeLength += 1;
            snakeX[snakeLength-1] = snakeX[snakeLength-2]+x;
            snakeY[snakeLength-1] = snakeY[snakeLength-2]+y;
            map[snakeX[snakeLength-1]][snakeY[snakeLength-1]] = SNAKE_HEAD;
        }
        else{
            movebody();
            movehead(x,y);
        }
        point++;
        creatfood();//创造新的食物
        return 1;
    }
    return 0;
}

int is_hitbody(int x,int y){
    if(map[snakeX[snakeLength-1]+x][snakeY[snakeLength-1]+y] == SNAKE_BODY)
        return 1;
    return 0;
}

int is_hitwall(int x,int y){
    if(map[snakeX[snakeLength-1]+x][snakeY[snakeLength-1]+y] == WALL_CELL)
        return 1;
    return 0;
}

void movebody(){//身体移动只需从尾巴到头部前一个位置，不断把前一个位置的坐标赋值给后一个位置即可
    map[snakeX[0]][snakeY[0]] = BLANK_CELL;
    for(int i = 0;i < snakeLength-1;i++){
        snakeX[i] = snakeX[i+1];
        snakeY[i] = snakeY[i+1];
        map[snakeX[i]][snakeY[i]] = SNAKE_BODY;
    }
}

void movehead(int x,int y){
    snakeX[snakeLength-1] = snakeX[snakeLength-1]+x;
    snakeY[snakeLength-1] = snakeY[snakeLength-1]+y;
    map[snakeX[snakeLength-1]][snakeY[snakeLength-1]] = SNAKE_HEAD;
}

void creatfood(){ //创造食物
    unsigned int times = (unsigned int)time(NULL);
	srand(times);
    foodX = rand()%9+1;
    foodY = rand()%9+1;
    while(1){
        int flag = 1;
        for(int i = 0;i < snakeLength-1;i++){ 
            //判断新创造的食物是否与蛇和墙有重合
            if(map[foodX][foodY] == SNAKE_BODY || map[foodX][foodY] == SNAKE_HEAD || map[foodX][foodY] == WALL_CELL){ 
                unsigned int times = (unsigned int)time(NULL);
	            srand(times*(i+1));
                foodX = rand()%9+1;
                foodY = rand()%9+1;
                flag = 0;
            }
        }
        if(flag == 1){
            break;
        }
    }
    map[foodX][foodY] = SNAKE_FOOD;
}

void output(){  //输出地图
    printf("======================\n");
    printf("     point:%d\n",point);
    for(int i = 0;i < 12;i++){
        printf("     ");
        for(int j = 0;j < 12;j++){
            printf("%c",map[i][j]);
        }
        printf("\n");
    }
    Sleep(1);//控制蛇的速度
}

int main(){
    gamestart();
    return 0;
}