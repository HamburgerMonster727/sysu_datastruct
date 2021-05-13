#include<stdio.h>
#include<stdlib.h>
#define Maxsize 20
#define IncreaseSize 20

typedef int Datatype;
typedef struct stack{
	Datatype *base;
	Datatype *top;
	int stacksize;
}Stack;

Stack* initStack(){
	Stack *s;
    s = (Stack*)malloc(sizeof(Stack));
	s->base = (Datatype*)malloc(Maxsize*sizeof(Datatype));
	s->top = s->base;
	s->stacksize = Maxsize;
	return s;
}

void push(Stack *s,Datatype data){
	if(s->top - s->base >= s->stacksize){
		s->base = (Datatype*)realloc(s->base,sizeof(Datatype)*(IncreaseSize + s->stacksize));
		s->stacksize = s->stacksize + IncreaseSize;
	}
	*(s->top) = data;
	s->top++;
}

void pop(Stack *s){
	if(s->top == s->base){
		return;
	}
	s->top--;
}

Datatype top(Stack *s){
	if(s->top != s->base){
		return *(s->top - 1);
	}
}

int main(){
    Stack *s;
	s = initStack();
	push(s,1);
    push(s,2);
    push(s,3);
	printf("%d ",top(s));
    pop(s);
    printf("%d ",top(s));
    pop(s);
    printf("%d ",top(s));
    pop(s);
	return 0;
}
