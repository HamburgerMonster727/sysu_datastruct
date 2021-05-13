#include<stdio.h>
#include<stdlib.h>

//二叉树
//typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;
struct TreeNode{
    int value;
    SearchTree left;
    SearchTree right;
};
 
//左孩子右兄弟树
typedef struct LCRStree *Tree;
struct LCRStree{
    int value;
    Tree LeftChild;
    Tree sibling;
};

SearchTree Insert(int x, SearchTree T){
    if(T == NULL){
        T = (SearchTree)malloc(sizeof(SearchTree));
        if(T == NULL){
            printf("error!\n");
            return NULL;
        }
        else{
            T->value = x;
            T->left = T->right = NULL;
            return T;
        }
    }
    else{
        if(x < T->value)
            T->left = Insert(x, T->left);
        else if(x > T->value)
            T->right = Insert(x, T->right);
        return T;
    }
}

Tree change(SearchTree T){
    Tree LCRS = (Tree)malloc(sizeof(Tree));
    LCRS->sibling = NULL;
    LCRS->LeftChild = NULL;
    LCRS->value = T->value;

    SearchTree tmp1[200];
    Tree tmp2[200];
    tmp1[0] = T;
    tmp2[0] = LCRS;
    int i1 = 1;
    int i2 = 1;

    while(tmp1[0] != NULL){
        //先检查有没有左孩子,有左孩子就先处理左孩子
        if (tmp1[0]->left){
            tmp1[i1] = tmp1[0]->left;
            i1++;
            Tree leftchild= (Tree)malloc(sizeof(Tree));
            leftchild->sibling = NULL;
            leftchild->LeftChild = NULL;
            leftchild->value = tmp1[0]->left->value;
            tmp2[0]->LeftChild = leftchild;
        //再检查有没有右孩子，有右孩子则处理右孩子
            if (tmp1[0]->right){
                tmp1[i1] = tmp1[0]->right;
                i1++;
                Tree sibling = (Tree)malloc(sizeof(Tree));
                sibling->value = tmp1[0]->right->value;
                sibling->sibling = NULL;
                sibling->LeftChild = NULL;
                leftchild->sibling = sibling;
                tmp2[i2] = leftchild;
                i2++;
                tmp2[i2] = sibling;
                i2++;
            }
        }
        //没有左孩子有右孩子的话把父亲的LeftChild指针赋值为右孩子的地址
        else{
            if(tmp1[0]->right){
                tmp1[i1] = tmp1[0]->right;
                i1++;
                Tree sibling = (Tree)malloc(sizeof(Tree));
                sibling->value = tmp1[0]->right->value;
                sibling->sibling = NULL;
                sibling->LeftChild = NULL;
                tmp2[0]->LeftChild = sibling;
                tmp2[i2] = sibling;
                i2++;
            }
        }
        if(i1 == 1){
            tmp1[0] = NULL;
            i1--;
        }
        else{
            for(int i = 0;i < i1-1;i++){
                tmp1[i] = tmp1[i+1];
            }
            i1--;
        }
        if(i2 == 1){
            tmp2[0] = NULL;
            i2--;
        }
        for(int i = 0;i < i2-1;i++){
            tmp2[i] = tmp2[i+1];
        }
        i2--;
    }
    return LCRS;
}

//后序遍历二叉树
void postOrderTraversal(SearchTree T){
    if (T != NULL){
        postOrderTraversal(T->left);
        postOrderTraversal(T->right);
        printf("%d ",T->value);
    }
}
 
//中序遍历左孩子右兄弟树
void InOrderTraversal(Tree T){
    if(T != NULL){
        InOrderTraversal(T->LeftChild);
        printf("%d ",T->value);
        InOrderTraversal(T->sibling);
    }
}
 
int main(){
    SearchTree T = NULL;
    int test[10] = {6,3,2,8,5,7,10,4,15,1};
    for (int i = 0; i < 10; i++){
        T = Insert(test[i], T);
    }
    postOrderTraversal(T);
    printf("\n");
    Tree LCRS = change(T);
    InOrderTraversal(LCRS);
    return 0;
}
