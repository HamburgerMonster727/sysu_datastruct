#include <stdio.h>
#include <stdlib.h> 
#define BUF_SIZE 10
#define true 1
#define false 0

typedef struct Queue{
    int * BUF;
    int front;
    int rear;
}QUEUE;

void initQueue(QUEUE *queue_q){
    queue_q->BUF = (int *)malloc(sizeof(int)*BUF_SIZE);
    if(queue_q->BUF != NULL){//队列内存分配成功
        queue_q->front = queue_q->rear = 0; //初始化头尾指针
    }
}

unsigned char is_fullQueue(QUEUE *queue_q){
    if((queue_q->rear +1)%BUF_SIZE == queue_q->front){
        return true;
    }
	else
        return false;
}

unsigned char is_emptyQueue(QUEUE *queue_q){
    if(queue_q->front == queue_q->rear){
        return true;
    }
    else
        return false;
}

void In_Queue(QUEUE *queue_q,int value){
    if(is_fullQueue(queue_q) != true){//队列未满
        queue_q->BUF[queue_q->rear] = value;
        queue_q->rear = (queue_q->rear + 1)%BUF_SIZE ;//尾指针偏移
    }
}

void out_Queue(QUEUE *queue_q,int *value){
    if(is_emptyQueue(queue_q) != true){//队列未空
    	*value = queue_q->BUF[queue_q->front];
        queue_q->front = (queue_q->front + 1)%BUF_SIZE ;
    }
}

void display(QUEUE *queue_q){
    if(is_emptyQueue(queue_q) != true){
        int ret = queue_q->front;
        while(ret != queue_q->rear){
            printf("%d  ",queue_q->BUF[ret]);
            ret = (ret+1)%BUF_SIZE;
        }
    }
    printf("\n");
}

int  main(){
    int val;
    QUEUE m;
    initQueue(&m);
    for(int i = 1;i <= 20;i++){
        In_Queue(&m,i);
    }
    display(&m);
    out_Queue(&m,&val);
    In_Queue(&m,9);
    display(&m);
    return 0;
}
