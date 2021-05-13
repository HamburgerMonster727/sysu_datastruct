#include<stdio.h>  
#include<stdlib.h>
#define true 1  
#define false 0
#define MAXNUM 20 
#define INFINITY 65535  

typedef char ElemType;  //顶点类型
typedef int Bool;
int visited[MAXNUM];  //全局数组,记录图中节点访问状态
int height[MAXNUM]; //记录节点层数

typedef struct EdgeNode{ //边表节点  
    int adjvex;    //该邻接点在顶点数组中的下标  
    int weight;    //边的权重
    struct EdgeNode *next;   //链域 指向下一个邻接点  
}EdgeNode;

typedef struct {
    int data;
    struct A *a,*b,*c;
}A,B;

typedef struct VertexNode{ //头节点
    ElemType data;  //顶点信息
    EdgeNode *firstedge;  //边表头指针(指向第一条依附于该顶点的弧的指针) 
}VertexNode,AdjList[MAXNUM]; //顶点数组(结构体数组)   

typedef struct Graph{  
    AdjList adjList;  
    int VertexNum,EdgeNum;//图中当前的结点数以及边数  
}Graph;

typedef struct Queue{//广度优先遍历需要的循环队列
    int data[MAXNUM];
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

Bool QueueFull(Queue *Q){
    if((Q->rear+1)%MAXNUM == Q->front)
        return true;
    else
        return false;
}

void EnQueue(Queue *Q,int e){
    if((Q->rear+1)%MAXNUM == Q->front)
        return;
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear+1)%MAXNUM;
}

void DeQueue(Queue *Q,int *e){
    if (Q->front == Q->rear)
        return;
    *e = Q->data[Q->front];
    Q->front = (Q->front+1)%MAXNUM;
}

void CreateALGraph(Graph *G){ 
    printf("输入图的结点数以及边数: "); 
    scanf("%d%d",&(G->VertexNum),&(G->EdgeNum));
    fflush(stdin);
    printf("===========================\n");
    printf("输入各个顶点的数据:\n");  
    for(int i = 0;i < G->VertexNum;++i){  
        printf("顶点%d: ",i+1);
        scanf("%c",&(G->adjList[i].data));  
        G->adjList[i].firstedge = NULL;  
        fflush(stdin);  
    }
    printf("===========================\n");
    for(int k = 0;k < G->EdgeNum;++k){
        int i,j,w; 
        printf("输入边(vi, vj)中的下标i和j和权W: ");
        scanf("%d%d%d",&i,&j,&w);
        EdgeNode *ptrEdgeNode = (EdgeNode*)malloc(sizeof(EdgeNode));
        ptrEdgeNode->adjvex = j;
        ptrEdgeNode->weight = w;
        ptrEdgeNode->next = G->adjList[i].firstedge;
        G->adjList[i].firstedge = ptrEdgeNode;
        //无向图需要加上以下代码
        ptrEdgeNode = (EdgeNode*)malloc(sizeof(EdgeNode));
        ptrEdgeNode->adjvex = i;
        ptrEdgeNode->weight = w;
        ptrEdgeNode->next = G->adjList[j].firstedge;
        G->adjList[j].firstedge = ptrEdgeNode;
    }
}

void PrintGraph(Graph *G){
    printf("==============================\n");
    printf("顶点序列为:\n");
    for(int i = 0;i < G->VertexNum;i++){
        printf("%3c",G->adjList[i].data);
    }
    printf("\n");
    printf("邻接表为:\n");
    for(int i = 0;i < G->VertexNum;i++){
        printf("%c: ",G->adjList[i].data);
        EdgeNode *p = G->adjList[i].firstedge;
        while(p){
            printf("-> |%c %d| ",G->adjList[p->adjvex].data,p->weight);
            p = p->next;
        }
        printf("\n");
    }
}

//DFS遍历
void DFS(Graph *G,int i){
    visited[i] = true;  
    printf("%3c",G->adjList[i].data);  
    EdgeNode *p = G->adjList[i].firstedge;
    while(p){
        if(!visited[p->adjvex]){
            DFS(G,p->adjvex); 
        }
        p = p->next;
    }
}

void DFSTraverse(Graph *G){
    printf("==============================\n");
    printf("深度遍历为:\n");
    for(int i = 0;i < G->VertexNum;++i){ 
        visited[i] = false;  
    }
    for(int i = 0;i < G->VertexNum;++i){
        if(!visited[i]){ 
            DFS(G,i);  //处理非联通图
        }
    }
    printf("\n");
}

//BFS遍历
void BFSTraverse(Graph *G){  
    printf("==============================\n");
    printf("广度优先遍历为:\n"); 
    Queue Q;  
    for(int i = 0;i < G->VertexNum;++i){  
        visited[i] = false; 
    } 
    for(int i = 0;i < G->VertexNum;++i){  
        height[i] = 0;  
    } 
    InitQueue(&Q);  
    for(int i = 0;i < G->VertexNum;++i){  
        if(!visited[i]){  
            visited[i] = true;  
            printf("%3c%d",G->adjList[i].data,height[i]);  
            EnQueue(&Q,i); 
            while(!QueueEmpty(&Q)){  
                DeQueue(&Q,&i);  
                EdgeNode *p = G->adjList[i].firstedge;  
                while(p){  
                    if(!visited[p->adjvex]){  
                        visited[p->adjvex] = true; 
                        height[p->adjvex] = height[i]+1; 
                        printf("%3c%d",G->adjList[p->adjvex].data,height[p->adjvex]);  
                        EnQueue(&Q,p->adjvex);  
                    }  
                    p = p->next;  
                }
            }
        }  
    }    
    printf("\n");
}

int main(){
    Graph *G;  
    G = (Graph*)malloc(sizeof(Graph));
    CreateALGraph(G); 
    PrintGraph(G);
    DFSTraverse(G); 
    BFSTraverse(G);
    return 0;
}