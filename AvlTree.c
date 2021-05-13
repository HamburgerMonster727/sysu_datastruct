#include <stdio.h>
#include <stdlib.h>
#define StopInput -999

typedef enum{
	False = 0,
	True = 1
}bool;
 
typedef struct AVLtree{
	int value;
	struct AVLtree *left,*right;
    int balance;
}AVLtree,*Tree;

void LeftBalance(Tree *root);
void RightBalance(Tree *root);

bool Insert(Tree *root,int value,bool *is_tall){
	if(NULL == *root){
		*root = (Tree)malloc(sizeof(AVLtree));
		if(NULL == *root)
			return False;
		(*root)->value = value;
		(*root)->left = (*root)->right = NULL;
		(*root)->balance = 0;
		*is_tall = True;
	}
	else{
		if(value < (*root)->value){
			if(Insert(&((*root)->left),value,is_tall) == False){
				return False; 
			}
			if(*is_tall){
				switch((*root)->balance){
					case 1:
						LeftBalance(root);
						*is_tall = False;
						break;
					case 0:
						(*root)->balance = 1;
						*is_tall = True;
						break;
					case -1:
						(*root)->balance = 0;
						*is_tall = False;
						break;
				}
			}
		}
		else if(value > (*root)->value){
			if(Insert(&((*root)->right),value,is_tall) == False){
				return False; 
			}
			if(*is_tall){
				switch((*root)->balance){
					case 1:
						(*root)->balance = 0;
						*is_tall = False;
						break;
					case 0:
						(*root)->balance = -1;
						*is_tall = True;
						break;
					case -1:
						RightBalance(root);
						*is_tall = False;
						break;
				}
			}
		}
	}
	return True;
}
 
void LeftRotate(Tree *root){
	Tree rightchild = (*root)->right;
	(*root)->right = rightchild->left;
	rightchild->left = *root;
	*root = rightchild;
}

void RightRotate(Tree *root){
	Tree leftchild = (*root)->left;
	(*root)->left = leftchild->right;
	leftchild->right = *root;
	*root = leftchild;
}
 
void LeftBalance(Tree *root){
	Tree leftchild = (*root)->left;
	Tree rightchild = leftchild->right;
	switch(leftchild->balance){
		case 1:
			(*root)->balance = leftchild->balance = 0;
			RightRotate(root);
			break;
		case -1:
			switch(rightchild->balance){
				case 1: 
					(*root)->balance = -1;
					leftchild->balance = 0;
					break;
				case 0:
					(*root)->balance = leftchild->balance = 0;
					break;
				case -1:
					(*root)->balance = 0;
					leftchild->balance = 1;
					break;
			}
			rightchild->balance = 0;
			LeftRotate(&((*root)->left));
			RightRotate(root);
			break;
	}
}
 
void RightBalance(Tree *root){
	Tree rightchild = (*root)->right;
	Tree leftchild = rightchild->left;
	switch(rightchild->balance){
		case -1:
			(*root)->balance = rightchild->balance = 0;
			LeftRotate(root);
			break;
		case 1:
			switch(leftchild->balance){
				case -1:
					(*root)->balance = 1;
					rightchild->balance = 0;
					break;
				case 0:
					(*root)->balance = rightchild->balance = 0;
					break;
				case 1:
					(*root)->balance = 0;
					rightchild->balance = -1;
					break;
			}
			leftchild->balance = 0;
			RightRotate(&((*root)->right));
			LeftRotate(root);
			break;
	}
}

void InOrder(Tree root){
	if(root != NULL){
		InOrder(root->left);
		printf("%d ",root->value);
		InOrder(root->right);
	}
}

int main(){
	Tree root = NULL;
	bool is_tall = False;
	int n;
	while(1){
        scanf("%d",&n);
        if(n == StopInput)
            break;
		Insert(&root,n,&is_tall);
    }
    InOrder(root);
    return 0;
}