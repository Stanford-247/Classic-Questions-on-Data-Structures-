#include <iostream>
#include <cstdlib>
#define OK 1
#define ERROR 0
#define OVERFLOW -1
using namespace std;

typedef int Status;
typedef struct BiNode{
    char data;//节点值
    struct BiNode *lchild;//左孩子
    struct BiNode *rchild;//右孩子
}BiTNode, *BiTree;

typedef struct SiNode{
    BiTree p;
    int state;//0访问左子树，1访问右子树
}SiNode;

SiNode a[10];//栈数组
int top = -1;//栈顶指针，-1表示栈为空

//入栈
Status postpush(SiNode *stack, SiNode s){
    if(top < 9){
        stack[++top] = s;
    }
    return OK;
}

//出栈
Status pop(){
    if(top != -1){
        top--;
    }
    return OK;
}

//输出节点值
Status displayElem(BiTree p){
    cout<<p->data<<' ';
    return OK;
}

//非递归后序遍历二叉树
Status InOrderTraverse(BiTree T){
    BiTree p = T;
    SiNode s;
    int state;
    while(p != nullptr || top != -1)
    {
        while(p != nullptr)
        {
            s.p = p;
            s.state = 0;
            postpush(a,s);
            p = p->lchild;
        }
        s = a[top];
        pop();
        p = s.p;
        state = s.state;
        if(state == 0)
        {
            s.state = 1;
            postpush(a, s);
            p = p->rchild;
        }
        else{
            displayElem(p);
            p = nullptr;
        }
    }
    return OK;
}

//构建二叉树
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
int main()
{
    BiTree T;
    CreateBiTree(T);
    InOrderTraverse(T);
    return 0;
}