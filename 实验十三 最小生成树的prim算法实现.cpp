#include <iostream>
#include <climits>
#define MAXVEX 100
using namespace std;

typedef struct{
    int vexs[MAXVEX]; //顶点数组
    int edge[MAXVEX][MAXVEX];//邻接矩阵
    int numv; //定点数
    int nume; //边数
}MGraph;

typedef struct{
    int adjvex; //最小边对应的已选顶点
    int lowcost;//最小边的权值，0表示顶点已加入生成树
}ClosedgeType;

//找到顶点在vexs数组中的下标
int Locate(MGraph G, int v)
{
    for(int i = 0; i < G.numv; i++)
    {
        if(G.vexs[i] == v)
            return i;
    }
    return -1;
}

//构建图
void InitGraph(MGraph &G){
    int i, j;
    cout<<"请输入图的顶点数：";
    cin>>G.numv;
    for(i = 0; i < G.numv; i++){
        cin >> G.vexs[i];
    }
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
        int a, b, w;
        cin>>a>>b>>w;
        int i = Locate(G, a);
        int j = Locate(G, b);
        G.edge[i][j] = w;
        G.edge[j][i] = w;
    }
}

//找到边权值最小的未选点
int minimum(ClosedgeType closedge[], int numv)
{
    int min_val = INT_MAX;
    int k = -1;
    for(int i = 0; i < numv; i++)
    {
        if(closedge[i].lowcost != 0 && closedge[i].lowcost < min_val)
        {
            min_val = closedge[i].lowcost;
            k = i;
        }
    }
    return k;
}

//prim算法实现
void MiniSpanTree_Prim(MGraph G, int u)
{
    ClosedgeType closedge[MAXVEX];
    int k = Locate(G, u);
    for(int j = 0; j < G.numv; j++)
    {
        if(j != k)
        {
            closedge[j].adjvex = u;
            closedge[j].lowcost = G.edge[k][j];
        }
        else{
            closedge[j].lowcost = 0;
        }
    }
    for(int i = 1; i < G.numv; i++)
    {
        k = minimum(closedge, G.numv);
        printf("边（%d,%d），权值=%d\n",closedge[k].adjvex, G.vexs[k], closedge[k].lowcost);
        closedge[k].lowcost = 0;
        for(int j = 0; j < G.numv; j++)
        {
            if (closedge[j].lowcost != 0 && G.edge[k][j] < closedge[j].lowcost) {
                    closedge[j].adjvex = G.vexs[k];
                    closedge[j].lowcost = G.edge[k][j];
            }
        }
    }
}

int main()
{
    MGraph G;
    int start;
    InitGraph(G);
    cout<<"请输入起点顶点值：";
    cin>>start;
    MiniSpanTree_Prim(G, start);
    return 0;
}