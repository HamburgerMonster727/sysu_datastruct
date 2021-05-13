#include<stdio.h>
#define maxsize 10000

void BucketSort(int array[],int n){
    int sort[maxsize] = {0};
    for(int i = 0;i < n;i++){
        sort[array[i]]++;
    }
    printf("排序后： ");
    int size = 0;
    for(int i = 0;i < maxsize;i++){
        if(size == n){
            break;
        }
        for(int j = 1;j <= sort[i];j++){
            printf("%d ",i);
            size++;
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
    BucketSort(array,num); 
    return 0; 
} 