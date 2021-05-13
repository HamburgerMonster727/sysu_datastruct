#include <stdio.h>
#include <stdlib.h>
#define MaxNum 20
#define QueueNum 8
#define true 1
#define false 0

typedef int Bool;

//队列结构
typedef struct Queue{
    int data[MaxNum];
    int front,rear;
}Queue;

void InitQueue(Queue *Q){
    Q->front = Q->rear = 0;
}

Bool QueueEmpty(Queue *Q){
    if (Q->front == Q->rear)
        return true;
    else
        return false;
}

void EnQueue(Queue *Q,int e){
    if((Q->rear+1)%MaxNum == Q->front)
        return;
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear+1)%MaxNum;
}

void DeQueue(Queue *Q){
    if(Q->front == Q->rear)
        return;
    Q->front = (Q->front+1)%MaxNum;
}

int Top(Queue *Q){
    if(Q->front == Q->rear)
        return -1;
    return Q->data[Q->front];
}

//小顶堆的操作
//对小顶堆进行调整
void HeapSortAdjust(Queue *queuearray[],int start,int end){ 
    int mark; 
    mark = Top(queuearray[start]); 
    Queue *tmp;
    tmp = queuearray[start];
    //从start这个父亲节点开始往他的儿子节点调整，若没超过范围，继续往儿子的儿子节点调整
    for(int i = 2*start;i <= end;i *= 2){
        //若左儿子大于右儿子，则i++，找到最小的儿子
        if(i+1 <= end && Top(queuearray[i]) > Top(queuearray[i+1])){
            i++; 
        } 
        //比较父亲和最小的儿子，如果父亲小于最小的儿子，则无需调整
        if(Top(queuearray[i]) > mark){
            break; 
        } 
        //若父亲大于最小的儿子，则把最小的儿子的值赋给父亲
        queuearray[start] = queuearray[i]; 
        start = i; 
    } 
    queuearray[start] = tmp; 
} 

//初始化创建一个小顶堆
void InitMinHeaps(Queue *queuearray[],int n){ 
    //从最底层的最右边的非叶子结点开始逐个逐层往上进行调整 
    for(int m = n/2;m > 0;m--){
        HeapSortAdjust(queuearray,m,n); 
    } 
} 

void swap(Queue *queuearray[],int i,int j){
    Queue *tmp; 
    tmp = queuearray[i]; 
    queuearray[i] = queuearray[j]; 
    queuearray[j] = tmp; 
} 

//交换第一个位置和n的值，然后对1到n-1范围进行小顶堆调整
void Pop(Queue *queuearray[],int n){
    if(n == 0){
        return;
    }
    swap(queuearray,1,n);
    HeapSortAdjust(queuearray,1,n-1);
}

//通过小顶堆和队列实现归并排序
int* MergeSortByMinHeap(Queue *queuearray[],int n){
    int *array;
    array = (int*)malloc(sizeof(int)*MaxNum*QueueNum);
    InitMinHeaps(queuearray,n);//先对队列数组进行小顶堆初始化
    int i = 0;
    while(n > 0){//n=0说明此时小顶堆内所有队列都为空
        if(QueueEmpty(queuearray[1])){//当队列为空时，将此队列出堆，对剩下的n-1个队列进行调整
            Pop(queuearray,n);
            n--;
        }
        if(!QueueEmpty(queuearray[1])){//当队列不为空时，出队，然后再对n个队列进行调整
            array[i] = Top(queuearray[1]);
            i++;
            DeQueue(queuearray[1]);
            HeapSortAdjust(queuearray,1,n);
        }
    }
    array[i] = -999;
    return array;
}

void test(){
    Queue **queuearray= (Queue**)malloc(sizeof(Queue*)*(QueueNum+1));
    for(int i = 1;i <= QueueNum;i++){
        queuearray[i] = (Queue*)malloc(sizeof(Queue));
        InitQueue(queuearray[i]);
        printf("从小到大输入第%d个队列的数据，输入为-999为停止输入\n",i);
        int e;
        while(1){
            scanf("%d",&e);
            if(e == -999)
                break;
            EnQueue(queuearray[i],e);
        }
    }
    int *array = MergeSortByMinHeap(queuearray,QueueNum);
    for(int i = 0;array[i] != -999;i++){
        printf("%d ",array[i]);
    }
}

int main(){
    test();
    return 0;
}