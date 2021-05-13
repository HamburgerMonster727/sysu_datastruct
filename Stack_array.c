#include<stdio.h>
#include<stdlib.h>
#define maxsize 10
typedef int datatype;

typedef struct stack{//数组实现栈
    datatype *data;
    int top;
	int realsize; 
}Stack;
void init(Stack *s){//初始化栈
    s->data = (datatype *)malloc(sizeof(datatype)*maxsize);
    s->top = -1;
	s->realsize = maxsize;
} 
int Empty(Stack *s){//判断栈是否为空
    if(s->top == -1){
        return 1;
    }
    else{
        return 0;
    }
}
void full(Stack *s){//判断栈是否已满了,栈满时扩展栈内存
    if(s->top == s->realsize-1){
        s->realsize = maxsize * 2;
        s->data = (datatype *)realloc(s->data,s->realsize * sizeof(datatype));
    }
}
void Push(Stack *s,datatype element){//入栈
    full(s);
    s->top++;
    s->data[s->top] = element;
}
void Pop(Stack *s){//出栈
    if(!Empty(s)){
        s->top--;
    }
}
datatype Top(Stack *s){//取栈顶元素
    if(!Empty(s)){
        return s->data[s->top];
    }
}
void Destroy(Stack *s){//销毁栈
    s->top = -1;
    free(s->data); 
}
void Print(Stack *s){//按格式输出栈
	if(!Empty(s)){
		Stack tmp = *s;
		int num = 1;
		printf("%d",Top(&tmp));
		Pop(&tmp);
		while(!Empty(&tmp)){
			if(num == 1 && Top(&tmp) > 0){
				printf(" + %dx",Top(&tmp));
				Pop(&tmp);
				num++;
			}
			else if(num == 1 && Top(&tmp) < 0){
				printf(" - %dx",-Top(&tmp));
				Pop(&tmp);
				num++;
			}
			else if(Top(&tmp) == 0){
				Pop(&tmp);
				num++;
			}
			else if(Top(&tmp) == 1){
				printf(" + x^%d",num);
				Pop(&tmp);
				num++;
			}
			else if(Top(&tmp) == -1){
				printf(" - x^%d",num);
				Pop(&tmp);
				num++;
			}
			else if(Top(&tmp) > 0){
				printf(" + %dx^%d",Top(&tmp),num);
				Pop(&tmp);
				num++;
			}
			else if(Top(&tmp) < 0){
				printf(" - %dx^%d",-Top(&tmp),num);
				Pop(&tmp);
				num++;
			}
		}
		printf("\n");
	}
	else{
		printf("Stack is empty!\n");
	}	
}
void Add(Stack s1,Stack s2){//两个栈取和
	Stack p1,p2,*s3,*s4,tmp1,tmp2;
	s3 = &p1;
	s4 = &p2;
	tmp1 = s1;
	tmp2 = s2;
	init(s3);
	init(s4);
	while(!Empty(&tmp1) && !Empty(&tmp2)){//将s1和s2取和入栈s3
		int data = Top(&tmp1) + Top(&tmp2);
		Pop(&tmp1);
		Pop(&tmp2);
		Push(s3,data);
	}
	while(!Empty(&tmp1)){
		int data = Top(&tmp1);
		Pop(&tmp1);
		Push(s3,data);
	}
	while(!Empty(&tmp2)){
		int data = Top(&tmp2);
		Pop(&tmp2);
		Push(s3,data);
	}
	while(!Empty(s3)){//将s3倒置入栈s4
		Push(s4,Top(s3));
		Pop(s3);
	}
	printf("sum of s1 and s2: ");
	Print(s4);
	Destroy(s3);
	Destroy(s4);
}

int main(){
	Stack p1,p2,*s1,*s2;
	s1 = &p1;
	init(s1);
    int data = 1;
	while(data != -999){//输入-999停止输入
		scanf("%d",&data);
		if(data != -999)
			Push(s1,data);
	}
	s2 = &p2;
	init(s2);
	data = 1;
	while(data != -999){
		scanf("%d",&data);
		if(data != -999)
			Push(s2,data);
	}
	printf("s1: ");
	Print(s1);
	printf("s2: ");
	Print(s2);
	Add(*s1,*s2);
	Destroy(s1);
	Destroy(s2);
	return 0;
}