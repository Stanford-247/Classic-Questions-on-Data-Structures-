#include <iostream>
#include <cstring>
#define MAXSIZE 100
#define OVERFLOW -1
#define OK 1
#define ERROR 0
using namespace std;

//栈的基本功能的实现
typedef int Status;
typedef struct{
    int data[MAXSIZE];
    int top;
}Stack;

Status InitStack(Stack &S)
{
    S.top = -1;
    return OK;
}

Status Push(Stack &S, int i)
{
    if(S.top == MAXSIZE - 1) return OVERFLOW;
    S.data[++S.top] = i;
    return OK;
}

int Pop(Stack &S)
{
    if(S.top == -1) return OVERFLOW;
    return S.data[S.top--];
}

bool StackEmpty(Stack &S)
{
    if(S.top == -1)
        return true;
    return false;
}

//图的邻接表存储结构
typedef struct EdgeNode{ //边结点
    int adjVex;  //边的终点在邻接表中的下标
    struct EdgeNode* next;  //指向下一条边
}EdgeNode;

typedef struct VexNode{ //顶点结点
    int data;  //顶点的实际值
    EdgeNode* firstEdge;  //该顶点出边链表的头指针
}VexNode;

typedef struct{
    VexNode adjList[MAXSIZE];
    int numVex;
    int numEdge;
}GraphAdjList;

int inDegree[MAXSIZE];//下标为i的顶点的入度

Status InitGraph(GraphAdjList& G){
    cout<<"请输入图的顶点数：";
    cin>>G.numVex;
    cout<<"请输入图的边数：";
    cin>>G.numEdge;
    for(int i = 0; i < G.numVex; i++)
    {
        cout<<"请输入顶点"<<i<<"的值：";
        cin>>G.adjList[i].data;
        G.adjList[i].firstEdge = NULL;
    }
    memset(inDegree, 0, sizeof(inDegree));
    for (int k = 0; k < G.numEdge; k++) {
        int v1, v2;
        cout << "请输入第" << k+1 << "条边（起点值 终点值）：";
        cin >> v1 >> v2;
        int startIdx = -1, endIdx = -1;
        for (int m = 0; m < G.numVex; m++) {
            if (G.adjList[m].data == v1) startIdx = m;
            if (G.adjList[m].data == v2) endIdx = m;
        }
        EdgeNode* newEdge = new EdgeNode;
        newEdge->adjVex = endIdx;
        newEdge->next = G.adjList[startIdx].firstEdge;
        G.adjList[startIdx].firstEdge = newEdge;
        inDegree[endIdx]++; // 终点的入度+1
    }
    return OK;
}

Status TopologicalSort(GraphAdjList G)
{
    Stack S;
    InitStack(S);               // 初始化栈
    int count = 0;
    int result[MAXSIZE];         // 结果数组
    int resIdx = 0;              // 结果数组的索引
    for(int i = 0; i < G.numVex; i++)
    {
        if(inDegree[i] == 0)
            Push(S, i);
    }
    while(!StackEmpty(S))
    {
        int topIdx = Pop(S);
        result[resIdx++] = G.adjList[topIdx].data;
        count++;
        // 遍历当前顶点的所有出边，解除对后续顶点的依赖
        EdgeNode* p = G.adjList[topIdx].firstEdge;
        while (p != NULL) {
            int adjVex = p->adjVex; // 出边的终点下标
            inDegree[adjVex]--;     // 终点入度-1（依赖减少1）
            if (inDegree[adjVex] == 0) { // 若终点无依赖，压入栈
                Push(S, adjVex);
            }
            p = p->next; // 遍历下一条出边
        }
    }
    cout << "栈实现的拓扑序列：";
    for (int i = 0; i < resIdx; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    return true;
}

int main(){
    GraphAdjList G;
    InitGraph(G);
    TopologicalSort(G);
    return 0;
}