#include<stdio.h>  
#include<stdlib.h>
#define true 1  
#define false 0
#define MAXNUM 100
#define INFINITY 65535  

typedef char ElemType;  //顶点类型
typedef int Bool;
int visited[MAXNUM];  //全局数组,记录图中节点访问状态
int enter[MAXNUM];  //每个顶点的入度

typedef struct EdgeNode{ //边表节点  
    int adjvex;    //该邻接点在顶点数组中的下标  
    int weight;    //边的权重
    struct EdgeNode *next;   //链域 指向下一个邻接点  
}EdgeNode;

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
        enter[i] = 0; 
        printf("顶点%d: ",i+1);
        scanf("%c",&(G->adjList[i].data));  
        G->adjList[i].firstedge = NULL;  
        fflush(stdin);  
    }
    printf("===========================\n");
    for(int k = 0;k < G->EdgeNum;++k){
        int i,j; 
        printf("输入边(vi, vj)中的下标i和j: ");
        scanf("%d%d",&i,&j);
        enter[j]++;
        EdgeNode *ptrEdgeNode = (EdgeNode*)malloc(sizeof(EdgeNode));
        ptrEdgeNode->adjvex = j;
        ptrEdgeNode->next = G->adjList[i].firstedge;
        G->adjList[i].firstedge = ptrEdgeNode;
        fflush(stdin);  
    }
}

void TopoSort(Graph *G){
    int size = G->VertexNum;
    Queue *Q = (Queue*)malloc(sizeof(Queue)); 
    InitQueue(Q);
    int TopoArray[size];//保存入队顺序
    int num = 0; //用于遍历Topo
    for(int i = 0;i < size;i++){
        visited[i] = false;
    }
    int IfTopo = 1;  //判断是否可以进行拓扑排序
    while(size > 0){
        int flag = 0;
        if(QueueEmpty(Q)){
            for(int i = 0;i < G->VertexNum;i++){
                if(visited[i] != true && enter[i] == 0){
                    flag = 1;
                }
            }
        }
        if(flag == 0){
            IfTopo = 0;
            printf("图有回环，无法拓扑排序\n");
            break;
        }
        for(int i = 0;i < G->VertexNum;i++){
            if(visited[i] != true && enter[i] == 0){
                EnQueue(Q,i);
                visited[i] = true;
                TopoArray[num] = i;
                num++;
            }
        }
        int j;
        while(!QueueEmpty(Q)){
            DeQueue(Q,&j);
            size--;
            EdgeNode *p = G->adjList[j].firstedge;  
            while(p){
                enter[p->adjvex]--;
                p = p->next;
            }
        }
    }
    if(IfTopo){
        for(int i = 0;i < num;i++){
            printf("%c ",G->adjList[TopoArray[i]].data);
        }
    }
}

int main(){
    Graph *G;  
    G = (Graph*)malloc(sizeof(Graph));
    CreateALGraph(G); 
    TopoSort(G);
    return 0;
}

