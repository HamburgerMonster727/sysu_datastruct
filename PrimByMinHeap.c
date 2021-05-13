#include <stdio.h>
#include <stdlib.h>

#define true 1  
#define false 0
#define MAXNUM 20 
#define INFINITY 2147483647  

typedef char ElemType;  
typedef int Bool;
int visited[MAXNUM+1];  //记录图中节点访问状态
int VertexInHeap[MAXNUM+1]; //记录图的节点在堆中的位置

typedef struct EdgeNode{ //边表节点  
    int adjvex;    //该邻接点在顶点数组中的下标  
    int weight;    //边的权重
    struct EdgeNode *next;   //指向下一个邻接点  
}EdgeNode;

typedef struct VertexNode{ //头节点
    ElemType data;  //顶点信息
    EdgeNode *firstedge;  //边表头指针
}AdjList; //顶点数组(结构体数组)   

typedef struct Graph{  
    AdjList adjList[MAXNUM+1];  //顶点数组
    int VertexNum,EdgeNum;//图中当前的结点数以及边数  
}Graph;

typedef struct Heap{//用于生成最小生成树的堆结构
    ElemType node; //节点信息
    int vertex;    //节点在原图的下标
    int parent;    //父亲在原图中的下标
    int distance;  //距离
}Heap;

//创建原图
void CreateALGraph(Graph *G){ 
    printf("输入图的结点数以及边数: "); 
    scanf("%d%d",&(G->VertexNum),&(G->EdgeNum));
    fflush(stdin);
    printf("===========================\n");
    printf("输入各个顶点的数据:\n");  
    for(int i = 1;i <= G->VertexNum;++i){  
        printf("顶点%d: ",i);
        scanf("%c",&(G->adjList[i].data));  
        G->adjList[i].firstedge = NULL;  
        fflush(stdin);  
    }
    printf("===========================\n");
    for(int k = 1;k <= G->EdgeNum;++k){
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

//对小顶堆进行调整
void HeapSortAdjust(Heap array[],int start,int end){ 
    Heap node; 
    node = array[start]; 
    int tmp = node.distance;
    //从start这个父亲节点开始往他的儿子节点调整，若没超过范围，继续往儿子的儿子节点调整
    for(int i = 2*start;i <= end;i *= 2){
        //若左儿子大于右儿子，则i++，找到最小的儿子
        if(i+1 <= end && array[i].distance > array[i+1].distance){
            i++; 
        } 
        //比较父亲和最小的儿子，如果父亲小于最小的儿子，则无需调整
        if(array[i].distance > tmp){
            break; 
        } 
        //若父亲大于最小的儿子，则把最小的儿子的值赋给父亲
        array[start] = array[i];
        VertexInHeap[array[start].vertex] = start;
        start = i; 
    } 
    array[start] = node; 
    VertexInHeap[array[start].vertex] = start;
} 

void swap(Heap array[],int i,int j){
    VertexInHeap[array[i].vertex] = j;
    VertexInHeap[array[j].vertex] = i;
    Heap tmp; 
    tmp = array[i]; 
    array[i] = array[j]; 
    array[j] = tmp; 
} 

//交换第一个位置和n的值，然后对1到n-1范围进行小顶堆调整
void Pop(Heap array[],int n){
    visited[array[1].vertex] = true; //把堆顶的节点的原图位置visited赋值为true
    swap(array,1,n);
    n--;
    for(int m = n/2;m > 0;m--){
        HeapSortAdjust(array,m,n); 
    }
}

//初始化堆
Heap* InitMinHeaps(Graph *G,int n){ 
    Heap *array = (Heap*)malloc(sizeof(Heap)*n);
    for(int i = 1;i <= n;i++){
        array[i].distance = INFINITY;
        array[i].node = G->adjList[i].data;
        array[i].parent = 0;
        array[i].vertex = i;
        VertexInHeap[i] = i;
    }
    return array;
} 

Graph* Prim(Graph *G){
    int size = G->VertexNum;
    int n = size;
    Heap *array = InitMinHeaps(G,size);  //对堆结构进行初始化
    int start = 1;  //从堆顶开始进行Prim
    array[start].distance = 0;  //把堆顶距离赋值为0
    for(int i = 1;i <= size;i++){
        visited[i] = false; //初始化visited
    }
    while(size > 0){
        int flag = 0; //用于判断当前节点的链接点的distance是否有改变
        EdgeNode *p = G->adjList[array[start].vertex].firstedge; //遍历堆顶的原图节点的边
        while(p){  
            if(!visited[p->adjvex]){
                int i = VertexInHeap[p->adjvex];   //寻找该p->adjvex在堆的位置i
                if(array[i].distance > p->weight){ //比较p->adjvex在堆里的距离和堆顶节点到p->adjvex的距离
                    array[i].distance = p->weight;
                    array[i].parent = array[start].vertex;
                    flag = 1;
                }
            }
            p = p->next;
        }
        if(flag == 1){
            Pop(array,size);
        }
        else{
            visited[array[1].vertex] = true;
            swap(array,1,size);
            HeapSortAdjust(array,1,size-1);
        }
        size--;
    }
    size = n;
    //根据heap来创建最小生成树
    Graph *MinSpanTree = (Graph*)malloc(sizeof(Graph));
    MinSpanTree->VertexNum = size;
    MinSpanTree->EdgeNum = size-1;
    for(int k = 1;k <= MinSpanTree->VertexNum;k++){
        MinSpanTree->adjList[k].data = G->adjList[k].data; //节点结构与原图相同
        MinSpanTree->adjList[k].firstedge = NULL;
    }
    for(int k = 1;k <= MinSpanTree->VertexNum;k++){
        int i,j,w;
        i = array[k].vertex; //获取堆内的边的数据
        j = array[k].parent;
        w = array[k].distance;
        if(j == 0)  
            continue;
        EdgeNode *ptrEdgeNode = (EdgeNode*)malloc(sizeof(EdgeNode));
        ptrEdgeNode->adjvex = j;
        ptrEdgeNode->weight = w;
        ptrEdgeNode->next = MinSpanTree->adjList[i].firstedge;
        MinSpanTree->adjList[i].firstedge = ptrEdgeNode;
        //无向图需要加上以下代码
        ptrEdgeNode = (EdgeNode*)malloc(sizeof(EdgeNode));
        ptrEdgeNode->adjvex = i;
        ptrEdgeNode->weight = w;
        ptrEdgeNode->next = MinSpanTree->adjList[j].firstedge;
        MinSpanTree->adjList[j].firstedge = ptrEdgeNode;
    }
    return MinSpanTree;
}

//打印邻接表
void PrintGraph(Graph *G){
    printf("==============================\n");
    printf("邻接表为:\n");
    for(int i = 1;i <= G->VertexNum;i++){
        printf("%c: ",G->adjList[i].data);
        EdgeNode *p = G->adjList[i].firstedge;
        while(p){
            printf("-> |%c %d| ",G->adjList[p->adjvex].data,p->weight);
            p = p->next;
        }
        printf("\n");
    }
}

int main(){
    Graph *G;  
    G = (Graph*)malloc(sizeof(Graph));
    CreateALGraph(G); 
    Graph *MinSpanTree = Prim(G);
    PrintGraph(MinSpanTree);
    return 0;
}