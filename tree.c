#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define MaxSize 100
 
struct tree {
    int data;
    struct tree* left;
    struct tree* right;
};
 
typedef struct queue{
    struct tree* numQ[MaxSize];
    int front;
    int rear;
}Queue;
 
Queue Q;
 
void initilize() { //初始化队列
    Q.front = 0;
    Q.rear = 0;
}
 
void Push(struct tree* root) { //入队
    Q.numQ[++Q.rear] = root;
}
 
struct tree* Pop() { //出队
    return Q.numQ[++Q.front];
}
 
int empty() { //判断对列是否为空
    return Q.rear == Q.front;
}
 
struct tree* creatTree (struct tree* root) {
    int value;
    scanf("%d", &value);
    if (value == -1)
        return NULL;
    root = (struct tree*)malloc(sizeof(struct tree));
    root->data = value;
    printf("请输入%d的左子树：", root->data);
    root->left = creatTree(root->left);
    printf("请输入%d的右子树：", root->data);
    root->right = creatTree(root->right);
    return root;
}
 
void LevelOrderTraversal (struct tree* root) { //二叉树的层次遍历
    struct tree* temp;
    Push(root);
    while (!empty()) {
        temp = Pop();
        printf("%d ", temp->data);  //输出队首结点
        if (temp->left)     //把Pop掉的结点的左子结点加入队列
            Push(temp->left);
        if (temp->right)    //把Pop掉的结点的右子结点加入队列
            Push(temp->right);
    }
}
 
int main() {
    printf("请输入头节点：");
    struct tree* root = creatTree(root);
    
    initilize();  //初始化队列
    
    LevelOrderTraversal(root);
    putchar('\n');
    
    return 0;
}

