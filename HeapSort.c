#include<stdio.h> 
#include<stdlib.h>
#include<time.h>
#include <windows.h>
#define maxsize 30

//对大顶堆进行调整
void HeapSortAdjust(int array[],int start,int end){ 
    int tmp; 
    tmp = array[start]; 
    //从start这个父亲节点开始往他的儿子节点调整，若没超过范围，继续往儿子的儿子节点调整
    for(int i = 2*start;i <= end;i *= 2){
        //若左儿子大于右儿子，则i++，找到最大的儿子
        if(i+1 <= end && array[i] < array[i+1]){
            i++; 
        } 
        //比较父亲和最大的儿子，如果父亲大于最小的儿子，则无需调整
        if(array[i] < tmp){
            break; 
        } 
        //若父亲小于最小的儿子，则把最小的儿子的值赋给父亲
        array[start] = array[i]; 
        start = i; 
    } 
    array[start] = tmp; 
} 

//把Push进来的数据放在最后一个位置，然后从该节点开始对父亲逐层往进行大顶堆调整
void Push(int array[],int data,int n){
    if(n == maxsize){
        return ;
    }
    n++;
    array[n] = data;
    for(int m = n/2;m > 0;m /= 2){
        HeapSortAdjust(array,m,n);
    }
}

//初始化创建一个大顶堆
void InitMaxHeaps(int array[],int n){ 
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

//交换第一个位置和n的值，然后对1到n-1范围进行大顶堆调整
int Pop(int array[],int n){
    if(n == 0){
        return -1;
    }
    int out = array[1];
    swap(array,1,n);
    HeapSortAdjust(array,1,n-1);
    return out;
}

//先对堆进行大顶堆初始化，然后从size=n到2进行Pop操作
void HeapSort(int array[],int n) { 
    int i; 
    InitMaxHeaps(array,n); 
    for(i = n;i > 1;i--) { 
        Pop(array,i);
    } 
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
    int num;
    printf("The numbers of data you want to input: ");
    scanf("%d",&num);
    int array[num+1];
    for(int i = 1;i <= num;i++){
        unsigned int times = (unsigned int)time(NULL);
		srand(times*(i+1));
        array[i] = rand() % 199 + 1;
        Sleep(500);
    }
    printf("排序前:\n"); 
    PrintHeaps(array,num);
    HeapSort(array,num); 
    printf("排序后:\n"); 
    PrintHeaps(array,num);
    return 0; 
} 
