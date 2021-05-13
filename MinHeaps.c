#include<stdio.h> 
#include<stdlib.h>
#include<time.h>
#define maxsize 30

//对小顶堆进行调整
void HeapSortAdjust(int array[],int start,int end){ 
    int tmp; 
    tmp = array[start]; 
    //从start这个父亲节点开始往他的儿子节点调整，若没超过范围，继续往儿子的儿子节点调整
    for(int i = 2*start;i <= end;i *= 2){
        //若左儿子大于右儿子，则i++，找到最小的儿子
        if(i+1 <= end && array[i] > array[i+1]){
            i++; 
        } 
        //比较父亲和最小的儿子，如果父亲小于最小的儿子，则无需调整
        if(array[i] > tmp){
            break; 
        } 
        //若父亲大于最小的儿子，则把最小的儿子的值赋给父亲
        array[start] = array[i]; 
        start = i; 
    } 
    array[start] = tmp; 
} 

//初始化创建一个小顶堆
void InitMinHeaps(int array[],int n){ 
    //从最底层的最右边的非叶子结点开始逐个逐层往上进行调整 
    for(int m = n/2;m > 0;m--){
        HeapSortAdjust(array,m,n); 
    } 
} 

void swap(int array[],int i,int j){
    int tmp; 
    tmp = array[i]; 
    array[i] = array[j]; 
    array[j] = tmp; 
} 

//把Push进来的数据放在最后一个位置，然后从该节点开始对父亲逐层往进行小顶堆调整
void Push(int array[],int data,int n){
    if(n == maxsize){
        return;
    }
    n++;
    array[n] = data;
    for(int m = n/2;m > 0;m /= 2){
        HeapSortAdjust(array,m,n);
    }
}

//交换第一个位置和n的值，然后对1到n-1范围进行小顶堆调整
int Pop(int array[],int n){
    if(n == 0){
        return -1;
    }
    int out = array[1];
    array[1] = 0;
    swap(array,1,n);
    HeapSortAdjust(array,1,n-1);
    return out;
}

void PrintHeaps(int array[],int n){
    if(n == maxsize){
        return;
    }
    for(int i = 1;i <= n;i++){
        printf("%-3d ",i);
    }
    printf("\n");
    for(int i = 1;i <= n;i++){
        printf("%-3d ",array[i]);
    }
    printf("\n");
}

int main(){ 
    int array[maxsize+1];
    int n;
    printf("The numbers of data you want to input: ");
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        array[i] = rand() % 99 + 1;
    }
    InitMinHeaps(array,n);
    PrintHeaps(array,n);

    int data = Pop(array,n--);
    printf("Pop: %d",data);
    printf("\n");
    PrintHeaps(array,n);

    data = rand() % 40 + 10;
    Push(array,data,n++);
    printf("Push: %d",data);
    printf("\n");
    PrintHeaps(array,n);

    data = Pop(array,n--);
    printf("Pop: %d",data);
    printf("\n");
    PrintHeaps(array,n);

    data = rand() % 30 + 20;
    Push(array,data,n++);
    printf("Push: %d",data);
    printf("\n");
    PrintHeaps(array,n);
    
    return 0; 
} 
