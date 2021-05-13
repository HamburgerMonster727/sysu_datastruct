#include<stdio.h>

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
    InsertSort(array,0,num-1); 
    printf("排序后："); 
    for(int i = 0;i < num;i++) { 
        printf("%d ",array[i]); 
    } 
    return 0; 
}