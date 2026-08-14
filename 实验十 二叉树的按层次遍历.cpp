#include <iostream>
#include <cstdlib>
#define OK 1
#define ERROR 0
#define OVERFLOW -1
using namespace std;

typedef int Status;
typedef char ElemType;
//创建树结点
typedef struct BiNode{
    char data;
    struct BiNode *lchild;
    struct BiNode *rchild;
}BiTNode, *BiTree;
//创建队列
typedef struct QNode{
    BiTree data;
    struct QNode *next;
}QNode, *QueuePtr;
typedef struct{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

//创建树
Status CreateBiTree(BiTree &T)
{
    char ch;
    cin>>ch;
    if(ch == '#')T = NULL;
    else{
        if(!(T = (BiTNode*)malloc(sizeof(BiTNode))))exit(OVERFLOW);
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
    return OK;
}

//创建队列
Status InitQueue(LinkQueue &Q)
{
    Q.front = (QueuePtr)malloc(sizeof(QNode));
    Q.rear = Q.front;
    Q.front->next = NULL;
    return OK;
}

//入队列
Status EnQueue(LinkQueue &Q, BiTree e)
{
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return OK;
}

//出队列
Status DeQueue(LinkQueue &Q, BiTree &e)
{
    if(Q.front == Q.rear)return ERROR;
    QueuePtr p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if(Q.rear == p)Q.rear = Q.front;//队列中只剩一个元素
    return OK;
}


//实现层序遍历
Status LevelOrderTraverse(BiTree T)
{
    BiTree p;
    LinkQueue qu;
    InitQueue(qu);
    EnQueue(qu, T);
    while(qu.front != qu.rear)
    {
        DeQueue(qu, p);
        cout<<p->data<<' ';
        if(p->lchild != NULL)EnQueue(qu, p->lchild);
        if(p->rchild != NULL)EnQueue(qu, p->rchild);
    }
    return OK;
}

int main()
{
    BiTree T;
    CreateBiTree(T);
    LevelOrderTraverse(T);
    return 0;
}