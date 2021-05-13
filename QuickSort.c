#include<stdio.h>
#define InsertSortSize 6

void InsertSort(int array[],int startIndex,int endIndex){
    for(int i = startIndex+1;i <= endIndex;i++){
        int key = array[i];
        int j = i-1;
        while(j >= startIndex && array[j] > key){
            array[j+1] = array[j];
            j = j-1;
        }
        array[j+1] = key;
    }
}

void QuickSort(int array[],int startIndex,int endIndex){
    if(endIndex - startIndex <= InsertSortSize){
        InsertSort(array,startIndex,endIndex);
    }
    else{
        if(endIndex <= startIndex){
            return;
        }
        int key = array[startIndex],i = startIndex - 1,j = endIndex + 1;
        while(i < j){
            do i++; while(array[i] < key); 
            do j--; while(array[j] > key);
            if(i < j){
                int tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
        }
        QuickSort(array,startIndex,j);
        QuickSort(array,j+1,endIndex);
    }
}

int main(){ 
    int num;
    scanf("%d",&num);
    int array[num],tmp[num];
    for(int i = 0;i < num;i++){
        scanf("%d",&array[i]);
    }
    printf("排序前："); 
    for(int i = 0;i < num;i++) { 
        printf("%d ",array[i]); 
    } 
    printf("\n");
    QuickSort(array,0,num-1); 
    printf("排序后："); 
    for(int i = 0;i < num;i++) { 
        printf("%d ",array[i]); 
    } 
    return 0; 
} 