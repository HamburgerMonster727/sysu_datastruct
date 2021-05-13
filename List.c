#include<stdio.h>
#include<stdlib.h>

typedef struct List{
    int val;
    List *next;
}List;

List* creatList() //创造 
{
    List * list = (List *)malloc(sizeof(List));
    list -> next = NULL;
    return list;
}
void addAtHead(List* myList,int val)  //头加 
{
    List * adds = creatList();
    adds-> val = val;
    adds -> next = myList->next;
    myList ->next = adds; 
}
int getValue(List* myList,int index)  //取值 
{
    for(int i=0;i<index;i++)
    {
        if(myList == NULL)
        return 0;
        myList = myList -> next;
    }
    return myList->val;
}
void addAtTail(List* myList,int val)  //尾加 
{
    while(myList->next!=NULL)
    {
        myList = myList -> next;
    }
    List * T =creatList();
    T -> val = val;
    T->next =NULL;
    myList ->next =T;
}
int addAtIndex(List* myList,int index,int val)  //插入 
{
    if(index <= 0)return 0;
    for(int i =0;i<index-1;i++){
        myList = myList -> next;
        if(myList==NULL)return 0;
    }
    List * adds =creatList();
    adds ->val = val;
    adds ->next = NULL;
    adds ->next = myList ->next;
    myList ->next =adds;
    return 1;
}
int deleteAtHead(List* myList)  //头删 
{
    if(myList->next == NULL)
    return 0;
    List * head = myList->next;
    myList -> next = head->next;
    free(head);
    return 1;
}
int deleteAtIndex(List* myList,int index) //删除 
{
    for(int i=0;i< index-1;i++)
    {
        if(myList==NULL)return 0;
        myList = myList ->next;
    }
    List * node =myList->next;
    if(node==NULL)return 0;
    else{
        myList->next = node->next;
    }
    free(node);
    return 1;
}
void printList(List* myList)  //打印 
{
    myList = myList->next;
    while(myList!=NULL)
    {
        printf("%d->",myList->val);
        myList = myList->next;
    }
    puts("null");
}
void freeList(List* myList) //释放 
{
    List * cur = myList;
    List * now = cur;
    while(now!=NULL)
    {
        cur= now;
        now = now-> next;
        free(cur);
    }
}
void reverseList(List* myList) {//反转 
	if(myList->next==NULL)
		return 0;
	List*prev=myList;
	myList=myList->next;
	List*p1=myList,*p2=myList->next,*p3=NULL;
	while(p2!=NULL){
		p1->next=p3;
		p3=p1;
		p1=p2;
		p2=p2->next;
	} 
	p1->next=p3;
	prev->next=p1;
};

void sortList(List *head){
	List *cur;
	List *min;
	List *move;
	int tmp;
	cur=head;
	while (cur->next!=NULL){
		min=cur;
		move=cur->next;
		while (move!=NULL){
			if (min->val < move->val)
				min=move;
			move=move->next;
		}
		if (min!=cur){
			tmp=cur->val;
			cur->val=min->val;
			min->val=tmp;
		}
		cur=cur->next;
	}
}

void insertNode(List *list, int added){
	List *cur;
	List *prev;
	List *addedNode;
	prev=NULL;	
	cur=list->next;
	addedNode=(List *)malloc(sizeof(List));
	addedNode->val=added;
	while ((cur!=NULL)&&(addedNode->val < cur->val)){  	
		prev=cur;		
		cur=cur->next;
	}
	if (prev==NULL){	
		addedNode->next=list->next;	
		list->next=addedNode; 
	}
    else{	
		prev->next=addedNode; 	
		addedNode->next=cur;
	}
}
