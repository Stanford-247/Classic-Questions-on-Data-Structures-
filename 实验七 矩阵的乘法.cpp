#include <iostream>
#define OK 1
#define ERROR 0
#define MAXSIZE 2500
#define MAXRC 50//矩阵最大行列数
using namespace std;

typedef int Status;
typedef struct{
    int i;
    int j;
    int e;
}Triple;
typedef struct{
    Triple data[MAXSIZE + 1];//非零元三元组表
    int rpos[MAXRC + 1];//各行第一个非零元的位置表
    int mu, nu, tu;//矩阵的行数、列数和非零元个数
}RLSMatrix;

//创建矩阵
Status CreateSMatrix(RLSMatrix &M)
{
    cout<<"请输入矩阵："<<endl;
    cin>>M.mu>>M.nu>>M.tu;
    for(int p = 1; p <= M.tu; p++)
    {
        cin>>M.data[p].i>>M.data[p].j>>M.data[p].e;
    }
    //构建rpos数组，记录每行第一个非零元的位置
    if(M.tu > 0)
    {
        int row = 1;
        M.rpos[row] = 1;
        for(int p = 2; p <= M.tu; p++)
        {
            if(M.data[p].i != M.data[p-1].i)
            {
                row = M.data[p].i;
                M.rpos[row] = p;
            }
        }
        for(int r = row + 1; r <= M.mu; r++)
        {
            M.rpos[r] = M.tu + 1;
        }
    }
    else{
        for(int r = 1; r <= M.mu; r++)
        {
            M.rpos[r] = 1;
        }
    }
    return OK;
}

//输出矩阵
Status PrintAMatrix(RLSMatrix M)
{
    cout<<"两矩阵相乘得到的矩阵为："<<endl;
    cout<<"行数："<<M.mu<<" 列数："<<M.nu<<" 非零元个数："<<M.tu<<endl;
    for(int p = 1; p <= M.tu; ++p)
    {
        cout<<M.data[p].i<<' '<<M.data[p].j<<' '<<M.data[p].e<<endl;
    }
    return OK;
}

Status MultSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix &Q)
{
    if(M.nu != N.mu)return ERROR;//判断左矩阵列数是否等于右矩阵行数以判断是否能进行矩阵乘法运算
    Q.mu = M.mu; Q.nu = N.nu; Q.tu = 0;
    if(M.tu * N.tu == 0)return OK;
    for(int arow = 1; arow <= M.mu; arow++)//处理M每一行
    {
        int ctemp[MAXRC + 1] = {0};//添加（更新）临时数组，用于临时存储累加计算结果
        Q.rpos[arow] = Q.tu + 1;
        //确定M第arow行非零元范围
        int p_start = M.rpos[arow];
        int p_end = (arow == M.mu) ? (M.tu + 1):M.rpos[arow + 1];
        for(int p = p_start; p < p_end; p++){//遍历矩阵M每一行的所有元素
            int brow = M.data[p].j;
            //确定N第brow行非零元的范围
            int q_start = N.rpos[brow];
            int q_end = (brow == N.mu)?(N.tu + 1):N.rpos[brow + 1];
            for(int q = q_start; q < q_end; q++){
                int ccol = N.data[q].j;//N当前非零元的列号=Q的列号
                ctemp[ccol] += M.data[p].e * N.data[q].e;
            }
        }
        //将ctemp中的非零元压缩存储到Q的三元组表
        for(int ccol = 1;ccol <= Q.nu; ccol++){
            if(ctemp[ccol] != 0){
                Q.tu++;
                Q.data[Q.tu].i = arow;
                Q.data[Q.tu].j = ccol;
                Q.data[Q.tu].e = ctemp[ccol];
            }
        }
    }
}

int main()
{
    RLSMatrix M, N, Q;
    CreateSMatrix(M);
    CreateSMatrix(N);
    MultSMatrix(M,N,Q);
    PrintAMatrix(Q);
    return 0;
}