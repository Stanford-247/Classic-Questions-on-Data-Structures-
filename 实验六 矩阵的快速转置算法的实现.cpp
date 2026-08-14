#include <iostream>
#define MAXSIZE 12500
#define OK 1
using namespace std;

typedef int Elemtype;
typedef int Status;
typedef struct{
    int i, j;//该非零元的行下标和列下标
    Elemtype e;
}Triple;
typedef struct{
    Triple data[MAXSIZE + 1];
    int mu, nu, tu;//矩阵的行数、列数和非零元个数
}TSMatrix;

Status TransposeSMatrix(TSMatrix M, TSMatrix &T){
    T.mu = M.nu;
    T.nu = M.mu;
    T.tu = M.tu;
    if(T.tu){
        int q = 1;//新转置矩阵的下标
        for(int col = 1;col <=M.nu; ++col)//从列号为1的元素开始查找
        {
            for(int p = 1;p <= M.tu;++p)//遍历原矩阵
            {
                if(M.data[p].j == col)
                {
                    T.data[q].i = M.data[p].j;//原矩阵的列给行
                    T.data[q].j = M.data[p].i;//原矩阵的行给列
                    T.data[q].e = M.data[p].e;//数值转移
                    ++q;
                }
            }
        }
    }
    return OK;
}//普通转置方法

Status FastTransposeSMatrix(TSMatrix M, TSMatrix &T){
    T.mu = M.nu;
    T.nu = M.mu;
    T.tu = M.tu;
    // 辅助数组1：num[col] 记录原矩阵第col列的非零元素个数
    int num[M.nu + 1] = {0};  
    // 辅助数组2：cpot[col] 记录转置后第col行的起始存储位置
    int cpot[M.nu + 1] = {0};
    if(T.tu){
        for(int col = 1;col <= M.nu; ++col) num[col] = 0;
        for(int t = 1;t <= M.tu; ++t) ++num[M.data[t].j];//求M中每一列含非零元个数
        cpot[1] = 1;
        //求第col列中第一个非零元在T.data中的序号，T是转置后的数组
        for(int col = 2;col <= M.nu; ++col) cpot[col] = cpot[col - 1] + num[col - 1];
        for(int p = 1;p <=M.tu; ++p)
        {
            int col = M.data[p].j;
            int q = cpot[col];//找到转置后数据的位置
            T.data[q].i = M.data[p].j;
            T.data[q].j = M.data[p].i;
            T.data[q].e = M.data[p].e;
            ++cpot[col];//更新位置，使得cpot数组中的内容始终保持为未进入转置后数组的第一个元素的位置
        }
    }
    return OK;
}

//创建稀疏矩阵M
Status CreateSMatrix(TSMatrix &M)
{
    cout<<"输入原矩阵："<<endl;
    cin>>M.mu>>M.nu>>M.tu;
    for(int p = 1;p <=M.tu;p++)
    {
        cin>>M.data[p].i>>M.data[p].j>>M.data[p].e;
    }
    return OK;
}

//输出稀疏矩阵
void PrintAMatrix(TSMatrix M)
{
    cout<<"转置后的矩阵为："<<endl;
    for(int p = 1;p <= M.tu;p++)
    {
        cout<<M.data[p].i<<' '<<M.data[p].j<<' '<<M.data[p].e<<endl;
    }
}

int main()
{
    TSMatrix M, T1, T2;
    CreateSMatrix(M);
    TransposeSMatrix(M, T1);
    PrintAMatrix(T1);
    FastTransposeSMatrix(M, T2);
    PrintAMatrix(T2);
    return 0;
}