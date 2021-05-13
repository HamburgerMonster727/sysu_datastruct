#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
#define MAXNUM 20
#define INFINITY 65535  

typedef int Bool;
typedef char ElemType;
int visited[MAXNUM];
int height[MAXNUM];

typedef struct{
    int VertexNum;//顶点数
    int EdgeNum;//边数
    ElemType vex[MAXNUM];//存储顶点
    int arc[MAXNUM][MAXNUM];//存储边关系
}Graph;        

//广度优先遍历需要的循环队列
typedef struct{
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

void EnQueue(Queue *Q,int e){
    if((Q->rear+1)%MAXNUM == Q->front)
        return;
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear+1)%MAXNUM;
}

void DeQueue(Queue *Q,int *e){
    if (Q->front == Q->rear)
        return ;
    *e = Q->data[Q->front];
    Q->front = (Q->front+1)%MAXNUM;
}

void CreateGraph(Graph *G){
    printf("输入顶点数和边数: ");
    scanf("%d%d",&G->VertexNum,&G->EdgeNum);
    printf("==============================\n");
    printf("输入各个顶点:\n");
    fflush(stdin);
    for(int i = 0;i < G->VertexNum;i++){
        printf("顶点%d: ",i+1);
        scanf("%c",&G->vex[i]);
        fflush(stdin);
    }
    for(int i = 0;i < G->VertexNum;i++){
        for(int j = 0;j < G->VertexNum;j++)
            G->arc[i][j] = INFINITY;
    }
    printf("==============================\n");
    for(int k = 0;k < G->EdgeNum;k++){
        int i,j,w;
        printf("输入边(vi, vj)中的下标i和j和权W: ");
        scanf("%d%d%d",&i,&j,&w);
        G->arc[i][j] = w;
        G->arc[j][i] = G->arc[i][j];
    }
    for(int i = 0;i < G->VertexNum;i++){
        G->arc[i][i] = 0;
    }
}

void PrintGraph(Graph *G){
    printf("==============================\n");
    printf("顶点序列为:\n");
    for(int v = 0;v < G->VertexNum;v++){
        printf("%3c", G->vex[v]);
    }
    printf("\n");
    printf("边的二维数组关系:\n");
    for(int i = 0;i < G->VertexNum; i++){
        for(int j = 0;j < G->VertexNum;j++){
            if(G->arc[i][j] == INFINITY){
                printf("  ∞");
            }
            else{
                printf("%3d",G->arc[i][j]);
            }
        }
        printf("\n");
    }
}

//DFS遍历
void DFS(Graph *G,int i){
    visited[i] = true;
    printf("%3c",G->vex[i]);
    for(int j = 0;j < G->VertexNum;++j){
        if(G->arc[i][j] != INFINITY && !visited[j])
            DFS(G,j);
    }
}

void DFSTraverse(Graph *G){
    printf("==============================\n");
    printf("深度遍历为:\n");
    for(int i = 0;i < G->VertexNum;++i)
        visited[i] = false;
    for(int i = 0;i < G->VertexNum;++i){
        if(!visited[i])
            DFS(G,i);
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
            printf("%3c%d",G->vex[i],height[i]);
            EnQueue(&Q,i); 
            while(!QueueEmpty(&Q)){
                DeQueue(&Q,&i);
                for(int j = 0;j < G->VertexNum;++j){
                    if(!visited[j] && G->arc[i][j] != INFINITY){
                        visited[j] = true;
                        height[j] = height[i]+1;
                        printf("%3c%d",G->vex[j],height[j]);
                        EnQueue(&Q,j);
                    }
                }
            }
        }
    }
    printf("\n");
}

int main(){
    Graph *G;
    G = (Graph*)malloc(sizeof(Graph));
    CreateGraph(G);
    PrintGraph(G);
    DFSTraverse(G);
    BFSTraverse(G);
    return 0;
}