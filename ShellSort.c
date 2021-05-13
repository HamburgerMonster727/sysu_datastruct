#include<stdio.h>

void ShellSort(int array[],int n){
    for(int gap = n/2;gap > 0;gap /= 2){  // 步长初始化为数组长度的一半，每次遍历后步长减半,
    	for(int i = 0;i < gap;++i){ 
	        for(int j = i + gap;j < n;j += gap){ //对步长为gap的元素进行直插排序，当gap为1时，就是直插排序
	            int tmp = array[j];  
	            int k = j-gap;  // j初始化为i的前一个元素（与i相差gap长度）
	            while(k >= 0 && array[k] > tmp){
	                array[k+gap] = array[k]; // 将在a[i]前且比tmp的值大的元素向后移动一位
	                k -= gap;
	            }
	            array[k+gap] = tmp; 
	        }
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
    for(int i = 0;i < num;i++){ 
        printf("%d ",array[i]); 
    } 
    printf("\n");
    ShellSort(array,num); 
    printf("排序后："); 
    for(int i = 0;i < num;i++){ 
        printf("%d ",array[i]); 
    } 
    return 0; 
} 