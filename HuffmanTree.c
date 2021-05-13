#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Huffman{
    int value;
    struct Huffman *left,*right;
}Tree;

Tree** init(int data[],int size){
    Tree **node = (Tree**)malloc(size*sizeof(Tree*));
    for(int i = 0;i < size;i++){
        node[i] = (Tree*)malloc(sizeof(Tree));
        node[i]->value = data[i];
        node[i]->left = NULL;
        node[i]->right = NULL;
    }
    return node;
}

Tree** ToHuffman(Tree *node[],int head,int size){
    for(int i = head;i < size-1;i++){
        int flag = i;
        for(int x = i + 1;x < size;x++){
            if(node[flag]->value > node[x]->value){
                flag = x;
            }
        }
        if(flag != i){
            Tree* temp = node[i];
            node[i] = node[flag];
            node[flag] = temp;
        }
    }
    Tree* newnode = (Tree*)malloc(sizeof(Tree));
    newnode->value = node[head]->value + node[head+1]->value;
    newnode->left = node[head];
    newnode->right = node[head+1];
    head++;
    node[head] = newnode;
    return node;
}

void HuffmanCode(Tree *head,char *code){
	if(head != NULL){
		if(head->left == NULL && head->right == NULL){
			printf("%d -> %s\n",head->value,code);
		}
		else{
			char tmp[50];
			strcpy(tmp,code);
			strcat(code,"0");
			HuffmanCode(head->left,code);
			strcpy(code,tmp);
			strcat(code,"1");
			HuffmanCode(head->right,code);
		}
	}
}

void Inorder(Tree* head){
    if(head != NULL){
    	printf("%d ",head->value);
        Inorder(head->left);
        Inorder(head->right);
    }
}

int main(){
    int size;
    int head = 0;
    scanf("%d",&size);
    int data[size];
    for(int i = 0;i < size;i++){
        scanf("%d",&data[i]);
    }
    Tree** node = init(data,size);
    while(head+1 != size){
        node = ToHuffman(node,head,size);
        head++; 
    }
    Inorder(node[head]);
	printf("\n");
	char str[50] = "";
	HuffmanCode(node[head],str);
    return 0;
}