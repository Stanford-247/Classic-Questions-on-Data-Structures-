#include <iostream>
#include<cstdlib>
#include<cstring>
#define OK 1
#define ERROR 0
#define OVERFLOW -1
using namespace std;

typedef int ElemType;
typedef int Status;
typedef struct OLNode{
    int i, j;//行下标、列下标
    ElemType e;
    struct OLNode *right, *down;
}OLNode, *OLink;
typedef struct{
    OLink *rhead, *chead;
    int mu, nu, tu;
}CrossList;

//以十字链表的形式创建表示稀疏矩阵
Status CreateSMatrix_OL(CrossList &M){
    cout<<"输入一个矩阵："<<endl;
    cin>>M.mu>>M.nu>>M.tu;
    if(!(M.rhead = (OLink*)malloc((M.mu + 1)*sizeof(OLink)))) exit(OVERFLOW);
    if(!(M.chead = (OLink*)malloc((M.nu + 1)*sizeof(OLink)))) exit(OVERFLOW);
    memset(M.rhead, 0, (M.mu + 1) * sizeof(OLink));  //内存初始化防止野指针
    memset(M.chead, 0, (M.nu + 1) * sizeof(OLink));
    for(int k = 0; k < M.tu;k++)
    {
        int i, j;
        ElemType e;
        cin>>i>>j>>e;
        OLink p = new OLNode();
        p->i = i;
        p->j = j;
        p->e = e;
        //插入到第i行的行链表
        if(M.rhead[i] == nullptr||M.rhead[i]->j > j)//若行链表为空或新节点列号小于第一个借点的列号则将新节点插到前头
        {
            p->right = M.rhead[i];
            M.rhead[i] = p;
        }
        else{//行链表非空，正常插入
            OLink q = M.rhead[i];
            while(q->right != nullptr&&q->right->j < j){
                q = q->right;
            }//通过循环查找插入位置
            p->right = q->right;
            q->right = p;
        }
        //插入到第j行的列链表
        if(M.chead[j] == nullptr||M.chead[j]->i > i)
        {
            p->down = M.chead[j];
            M.chead[j] = p;
        }
        else{
            OLink q = M.chead[j];
            while(q->down != nullptr&&q->down->i < i){
                q = q->down;
            }
            p->down = q->down;
            q->down = p;
        }
    }
    return OK;
}

//实现稀疏矩阵的加法
Status AddSMatrix_OL(CrossList &A, CrossList &B, CrossList &C)
{
    if(A.mu != B.mu||A.nu != B.nu) return ERROR;
    C.mu = A.mu;
    C.nu = A.nu;
    C.tu = 0;
    C.rhead = new OLink[C.mu + 1]();
    C.chead = new OLink[C.nu + 1]();
    for(int i = 1; i <= C.mu; i++)
    {
        OLink p = A.rhead[i];
        OLink q = B.rhead[i];
        OLink *row_prev = &C.rhead[i];  // 指向行链表当前最后一个节点的指针
        
        while(p != nullptr || q != nullptr)
        {
            OLink newnode = nullptr;            
            // 处理三种情况
            if(q == nullptr || (p != nullptr && p->j < q->j))
            {
                // 只处理A的节点
                newnode = new OLNode();
                newnode->i = i;
                newnode->j = p->j;
                newnode->e = p->e;
                newnode->right = nullptr;
                newnode->down = nullptr;
                p = p->right;
            }
            else if(p == nullptr || (q != nullptr && p->j > q->j))// 只处理B的节点
            {  
                newnode = new OLNode();
                newnode->i = i;
                newnode->j = q->j;
                newnode->e = q->e;
                newnode->right = nullptr;
                newnode->down = nullptr;
                q = q->right;
            }
            else// 行列相同，相加
            {  
                ElemType sum = p->e + q->e;
                if(sum != 0)
                {
                    newnode = new OLNode();
                    newnode->i = i;
                    newnode->j = p->j;
                    newnode->e = sum;
                    newnode->right = nullptr;
                    newnode->down = nullptr;
                }
                p = p->right;
                q = q->right;
            }            
            // 如果创建了新节点，插入到C中
            if(newnode != nullptr)
            {
                // 插入行链表
                *row_prev = newnode;
                row_prev = &(newnode->right);
                
                // 插入列链表
                OLink *col_prev = &C.chead[newnode->j];
                while(*col_prev != nullptr && (*col_prev)->i < i)
                {
                    col_prev = &((*col_prev)->down);
                }
                newnode->down = *col_prev;
                *col_prev = newnode;                
                C.tu++;
            }
        }
    }
    return OK;
}

//输出矩阵
Status PrintSMatrix_OL(CrossList &M)
{
    cout<<"两矩阵之和为："<<endl;
    for(int i = 1; i <= M.mu;i++)//遍历行
    {
        OLink p = M.rhead[i];
        while(p != nullptr)//遍历该行每一列
        {
            cout<<p->i<<' '<<p->j<<' '<<p->e<<endl;
            p = p->right;
        }
    }
    return OK;
}

int main()
{
    CrossList A, B, C;
    CreateSMatrix_OL(A);
    CreateSMatrix_OL(B);
    AddSMatrix_OL(A, B, C);
    PrintSMatrix_OL(C);
    return 0;
}