#include<stdio.h>
#include<math.h>

/* 获取输入数字的索引值，dec指定数字的位数，3代表百位数，order指定需要获取哪一位的索引，1代表个位，2代表十位，3代表百位 */
int get_index(int num,int dec,int order){
    /* 根据位数，循环减去不需要的高位数字 */
    for(int i = dec;i > order;i--) {
        int div = num/pow(10,dec-1);
        num -= div*pow(10,dec-1);
        dec--;
    }
    int index = num/pow(10,order-1);
    return index;
}
 
void RadixSort(int array[],int len,int dec,int order){
    if(dec < order) 
        return;
    int index;    
    int tmp[len]; 
    int num[10];  
    memset(tmp,0,len*sizeof(int)); 
    memset(num,0,10*sizeof(int));  
    for(int i = 0;i < len;i++){
        index = get_index(array[i],dec,order); 
        num[index]++;  
    }
    for(int i = 1;i < 10;i++){
        num[i] += num[i-1]; /* 调整索引数组 */
    }
    for(int i = len-1;i >= 0;i--){
        index = get_index(array[i],dec,order);  
        int j = --num[index];  /* 根据索引计算该数字在按位排序之后在数组中的位置 */
        tmp[j] = array[i]; 
    }
    for(int i = 0;i < len;i++){
        array[i] = tmp[i];
    } 
    RadixSort(array,len,dec,order+1);
    return;
}
 
int main(){
    int num = 30;  /* 测试数据个数 */
    int dec = 3;   /* 数据位数，3代表3位数 */
    int array[30] = {258, 65, 515, 337, 359, 701, 916, 494, 303, 175,
                        677, 825, 131, 560, 147, 254, 759, 814, 917, 382,
                        452, 114, 873, 585, 881, 127, 819, 658, 461, 435};
    printf("排序前：");
    for(int i = 0;i < num;i++){
        printf("%d ",array[i]);
    }
    printf("\n");
    RadixSort(array,num,dec,1);
    printf("排序后：");
    for(int i = 0;i < num;i++){
        printf("%d ",array[i]);
    }
    printf("\n");
    return 0;
}