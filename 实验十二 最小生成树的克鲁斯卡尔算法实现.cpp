#include <iostream>
#include<climits>
#define MAXVEX 100
#define MAXSIZE 1000
using namespace std;

typedef struct
{
    int begin;
    int end;
    int weight;
}Edge;

typedef struct{
    int numv;//图的定点数
    int nume;//图的边数
    int edge[MAXVEX][MAXVEX];//邻接矩阵
}MGraph;

//构建图
void InitGraph(MGraph &G){
    int i, j;
    cout<<"请输入图的顶点数：";
    cin>>G.numv;
    //初始化邻接矩阵
    for(i = 0; i < G.numv;i++)
    {
        for(j = 0; j < G.numv;j++)
        {
            if(i == j)G.edge[i][j] = 0;
            else G.edge[i][j] = INT_MAX;
        }
    }
    cout<<"请输入图的边数：";
    cin>>G.nume;
    for(int k = 0; k < G.nume; k++)
    {
        int i, j, w;
        cin>>i>>j>>w;
        G.edge[i][j] = w;
        G.edge[j][i] = w;
    }
}

//提取有效边并按权值从小到大排序
void OperationEdge(MGraph G, Edge* edges)
{
    int i, j, k;
    k = 0;
    for( i = 0; i < G.numv;i++)
    {
        for( j = i + 1; j < G.numv;j++)
        {
            if(G.edge[i][j] != INT_MAX&&G.edge[i][j] != 0)
            {
                edges[k].begin = i;
                edges[k].end = j;
                edges[k].weight = G.edge[i][j];
                k++;
            }
        }
    }
    Edge temp;
    for(i = 0; i < k; i++)
    {
        for(j = i + 1; j < k; j++)
        if (edges[i].weight > edges[j].weight) {
                temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
    }
}

//查找根
int Find(int *parent, int f)
{
    while(parent[f] > 0)
    {
        f = parent[f];
    }
    return f;
}

//Kruskal算法
void MinSpanTree_Kruskal(MGraph G)
{
    int i, n, m;
    Edge edges[MAXSIZE];//存储所有有效边的权值
    int parent[MAXVEX];
    OperationEdge(G, edges);
    //初始化，每个顶点表示独立的根
    for(i = 0; i < G.numv; i++)
    {
        parent[i] = 0;
    }
    cout << "Kruskal算法生成的最小生成树边集：" << endl;
    int totalWeight = 0;
    for(int i = 0; i < G.nume; i++)
    {
        n = Find(parent, edges[i].begin);
        m = Find(parent, edges[i].end);
        if(n != m)
        {
            parent[n] = m;
            printf("边（%d, %d），权值 = %d\n", edges[i].begin, edges[i].end, edges[i].weight);
            totalWeight += edges[i].weight;
        }
    }
    cout << "最小生成树的总权值：" << totalWeight << endl;
}

int main() {
    MGraph G;
    InitGraph(G);
    MinSpanTree_Kruskal(G);
    return 0;
}