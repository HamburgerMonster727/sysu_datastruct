#include <stdio.h>
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

void Merge(int array[],int startIndex,int midIndex,int endIndex){
    int tmp[endIndex+1];
    int i = startIndex,j = midIndex+1,k = startIndex;
    while(i != midIndex+1 && j != endIndex+1){
        if(array[i] > array[j])
            tmp[k++] = array[j++];
        else
            tmp[k++] = array[i++];
    }
    while(i != midIndex+1)
        tmp[k++] = array[i++];
    while(j != endIndex+1)
        tmp[k++] = array[j++];
    for(i = startIndex;i <= endIndex;i++)
        array[i] = tmp[i];   
}

void MergeSort(int array[],int startIndex,int endIndex){
    int midIndex;
    if(startIndex < endIndex){
        if(endIndex - startIndex <= InsertSortSize){
            InsertSort(array,startIndex,endIndex);
        }
        else{
            midIndex = startIndex+(endIndex-startIndex)/2;       
            MergeSort(array,startIndex,midIndex);
            MergeSort(array,midIndex+1,endIndex);    
            Merge(array,startIndex,midIndex,endIndex);
        }
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
    MergeSort(array,0,num-1); 
    printf("排序后："); 
    for(int i = 0;i < num;i++) { 
        printf("%d ",array[i]); 
    } 
    return 0; 
} 