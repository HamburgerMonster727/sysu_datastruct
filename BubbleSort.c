#include<stdio.h> 

void BubbleSort(int array[],int n){
    for(int i = 0;i < n-1;i++){
        int flag = 1;
        for(int j = 0;j < n-1-i;j++){
            if(array[j] > array[j+1]){
                int tmp = array[j];
                array[j] = array[j+1];
                array[j+1] = tmp;
                flag = 0;
            }
        }
        if(flag == 1){
            break;
        }
    }
}

int main(){
    int num;
    scanf("%d",&num);
    int array[num];
    for(int i = 0;i < num;i++){
        scanf("%d",&array[i]);
    }
    printf("排序前："); 
    for(int i = 0;i < num;i++) { 
        printf("%d ",array[i]); 
    } 
    printf("\n");
    BubbleSort(array,num); 
    printf("排序后："); 
    for(int i = 0;i < num;i++) { 
        printf("%d ",array[i]); 
    } 
    return 0; 
}