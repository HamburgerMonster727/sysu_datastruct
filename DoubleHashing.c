#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

typedef struct Hashing{
    int value;
    int occupy;
}DoubleHashing;

void init(DoubleHashing Hashing[],int size){
    for(int i = 0;i < size;i++){
        Hashing[i].occupy = 0;
        Hashing[i].value = 0;
    }
}

void ToDoubleHashing(DoubleHashing Hashing[],int data,double *average){
    int Binaray[12];
    int tmp = data;
    for(int i = 0;i < 12;i++){
        Binaray[i] = tmp % 2;
        tmp = tmp / 2;
    } 
    int index = 0;
    int jump = 0;
    for(int i = 0;i < 6;i++){
        index = index + Binaray[i] * pow(2,i);
    }
    if(Hashing[index].occupy == 0){
        Hashing[index].value = data;
        Hashing[index].occupy = 1;
        *average = *average + 1;
    }
    else{
        for(int i = 6;i < 12;i++){
            jump = jump + Binaray[i] * pow(2,i-6);
        }
        if(jump % 2 == 0){
            jump = jump | 1;
        }
        while(1){
            index = (index + jump) & (64 - 1);
            *average = *average + 1;
            if(Hashing[index].occupy == 0){
                Hashing[index].value = data;
                Hashing[index].occupy = 1;
                break;
            }
        }
    }
}

void PrintHashing(DoubleHashing Hashing[]){
    printf("The DoubleHashing table:\n");
    for(int x = 0;x < 64;x += 8){
        for(int i = x;i < x + 8;i++){
            printf("%d\t",i);
        }
        printf("\n");
        for(int i = x;i < x + 8;i++){
            printf("%d\t",Hashing[i].value);
        }
        printf("\n\n");
    }
}

int main(){
    int size = 40;
    DoubleHashing Hashing[64];
    init(&Hashing,64);
    int data[size];
    srand((unsigned int)time(0));
    for(int i = 0;i < size;i++){
        data[i] = rand() % 4094 + 1;
        Sleep(1000);
    }
    printf("The data input:\n");
    for(int i = 0;i < size;i++){
        printf("%-4d ",data[i]);
        if(i % 10 == 9)
            printf("\n");
    }
    double average = 0;
    for(int i = 0;i < size;i++){
        ToDoubleHashing(&Hashing,data[i],&average);
    }
    double n = average / size;
    printf("The average number of probes is %lf\n",n);
    PrintHashing(Hashing);
    return 0;
}