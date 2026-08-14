#include <iostream>
#include <cstdlib>
#include <cstring>
#include <climits>
using namespace std;

typedef struct{
    unsigned int weight;//结点权值
    unsigned int parent, lchild, rchild;//结点索引，不存在为0
}HTNode, *HuffmanTree;
typedef char **HuffmanCode;//二级指针，本质是“字符串数组”

//选择函数，选出所有结点中权值最小的两个结点
void Select(HuffmanTree HT, int i, int &s1, int &s2)
{
    unsigned int min1 = UINT_MAX;
    unsigned int min2 = UINT_MAX;
    s1 = s2 = 0;
    for(int j = 1; j <= i; j++)
    {
        if(HT[j].parent == 0)
        {
            if(HT[j].weight < min1)
            {
                min2 = min1;
                s2 = s1;
                min1 = HT[j].weight;
                s1 = j;
            }//权值最小的结点
            else if(HT[j].weight < min2)
            {
                min2 = HT[j].weight;
                s2 = j;
            }//权值第二小的结点
        }
    }
}

//构造哈夫曼树并求哈夫曼编码
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n)
//HT代表构建好的哈夫曼树，HC代表生成的哈夫曼编码表，w代表输入的权值数组，n代表权值的个数
{
    if(n <= 1)return;
    int m = 2 * n - 1;//哈夫曼树的总结点数=n个叶子结点+（n-1）个非叶子结点
    HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
    for(int i = 1; i <= n; i++) {
    HT[i].weight = (unsigned int)w[i-1];
    HT[i].parent = 0;
    HT[i].lchild = 0;
    HT[i].rchild = 0;
    }//前n个结点为叶子结点，对其进行初始化
    for(int i = n + 1; i <= m; i++) {
        HT[i].weight = 0;//后续赋值时计算
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }//其余结点为非叶子结点，初始化，所有结点的索引在后续操作过程中变化
    for(int i = n + 1; i <= m; ++i){//建哈夫曼树
        int s1, s2;
        Select(HT, i - 1, s1, s2);
        HT[s1].parent = i;
        HT[s2].parent = i;//s1,s2的父结点设为i
        HT[i].lchild = s1;
        HT[i].rchild = s2;//s1,s2分别为新结点的左右子结点
        HT[i].weight = HT[s1].weight + HT[s2].weight;//新结点权值等于两子结点权值之和
    }
    //从叶子到根逆向求每个字符的哈夫曼编码
    HC = (HuffmanCode)malloc((n + 1)*sizeof(char *));//编码表
    char *cd = (char *)malloc(n * sizeof(char));//临时存放单个编码
    cd[n - 1] = '\0';//编码结束符
    for(int i = 1; i <= n; ++i)//遍历每个叶子结点
    {
        int start = n - 1;
        int c = i;//当前结点
        int f = HT[i].parent;//父节点索引
        while(f != 0)//父结点存在
        {
            if(HT[f].lchild == c) cd[--start] = '0';
            else cd[--start] = '1';//从右往左编码
            c = f;
            f = HT[f].parent;
        }
        HC[i] = (char *)malloc((n - start)*sizeof(char));
        strcpy(HC[i], &cd[start]);
    }
    free(cd);
}

void Print(HuffmanCode HC, int *w, int n)
{
    cout<<"权值对应的哈夫曼编码："<<endl;
    for(int i = 1; i <= n; i++)
        cout<<w[i-1]<<':'<<HC[i]<<endl;
}

int main()
{
    int n = 6;
    int w[] = {5, 9, 12, 13, 16, 45};
    HuffmanTree HT;
    HuffmanCode HC;
    HuffmanCoding(HT, HC, w, n);
    Print(HC, w, n);
    for(int i = 1; i <= n; i++) free(HC[i]);
    free(HC);
    free(HT);//释放内存空间
    return 0;
}