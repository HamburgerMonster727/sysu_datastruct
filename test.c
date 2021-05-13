#include <stdio.h>
#include <stdlib.h>
int main(){
    int number = 10;
    int *node = (int*)malloc(sizeof(int)*number);
    node[0] = 1;
}
