#include <iostream>
#include <climits>
#define MAXVEX 100
using namespace std;

// 边节点结构
typedef struct ArcNode {
    int adjvex;               // 邻接点的顶点索引
    int weight;               // 边的权值
    struct ArcNode* nextarc;  // 指向下一个边节点
} ArcNode;

// 顶点节点结构
typedef struct VNode {
    int data;                 // 顶点存储的数据
    ArcNode* firstarc;        // 指向第一个边节点
} VNode;

// 邻接链表表示的图
typedef struct {
    VNode adjlist[MAXVEX];    // 顶点数组
    int vexnum, arcnum;       // 顶点数、边数
} ALGraph;

// 创建邻接链表
void CreateALGraph(ALGraph &G) {
    cout << "请输入顶点数、边数：";
    cin >> G.vexnum >> G.arcnum;

    // 初始化顶点
    for (int i = 0; i < G.vexnum; i++) {
        cout << "请输入顶点" << i << "的值：";
        cin >> G.adjlist[i].data;
        G.adjlist[i].firstarc = NULL; 
    }
    for (int i = 0; i < G.arcnum; i++) {
        cout << "请输入第" << i + 1 << "条边：";
        int a, b, w;
        cin >> a >> b >> w;
        int x = -1, y = -1;
        for (int k = 0; k < G.vexnum; k++) {
            if (G.adjlist[k].data == a) x = k;
            if (G.adjlist[k].data == b) y = k;
        }

        // 创建边节点并插入邻接表
        if (x != -1 && y != -1) {
            ArcNode* p = new ArcNode;
            p->adjvex = y;
            p->weight = w;
            p->nextarc = G.adjlist[x].firstarc; 
            G.adjlist[x].firstarc = p;
        }
    }
}

// P是路径矩阵，记录源点到每个顶点的最短路径上包含的结点，P[v][w] = true表示顶点w是源点到顶点v的最短路径上的节点
// D用来表示源点v0到顶点v的最短路径长度
// final用来表示顶点v的最短路径是否确定
void Dijkstra(ALGraph G, int v0, int D[], bool P[][MAXVEX]) {
    bool final[MAXVEX]; // 表示顶点最短路径已确定
    // 初始化
    for (int v = 0; v < G.vexnum; v++) {
        final[v] = false;
        D[v] = INT_MAX;
        for (int w = 0; w < G.vexnum; w++) {
            P[v][w] = false;
        }
        ArcNode* p = G.adjlist[v0].firstarc;// v0到v的直接边
        while (p != NULL) {
            if (p->adjvex == v) {
                D[v] = p->weight;
                break;
            }
            p = p->nextarc;
        }
        if (D[v] < INT_MAX) {
            P[v][v0] = true;
            P[v][v] = true;
        }
    }
    D[v0] = 0;
    final[v0] = true;
    P[v0][v0] = true;

    for (int i = 1; i < G.vexnum; i++) {
        // 找到当前距离最小的未确定顶点v
        int min = INT_MAX;
        int v = -1;
        for (int w = 0; w < G.vexnum; w++) {
            if (!final[w] && D[w] < min) {
                v = w;
                min = D[w];
            }
        }
        if (v == -1) break;
        final[v] = true;

        // 更新v的所有邻接顶点的距离
        ArcNode* p = G.adjlist[v].firstarc;
        while (p != NULL) {
            int w = p->adjvex; // 邻接顶点的索引
            int weight = p->weight; // 边v->w的权值
            if (!final[w] && D[v] != INT_MAX && (D[v] + weight < D[w])) {
                D[w] = D[v] + weight;
                // 复制路径
                for (int k = 0; k < G.vexnum; k++) {
                    P[w][k] = P[v][k];
                }
                P[w][w] = true;
            }

            p = p->nextarc; // 遍历下一个邻接顶点
        }
    }
}

// 输出路径
void PrintPath(ALGraph G, int v0, int D[], bool P[][MAXVEX]) {
    cout << "\n源点" << G.adjlist[v0].data << "到各顶点的最短路径信息：" << endl;
    for (int v = 0; v < G.vexnum; v++) {
        cout << "到顶点" << G.adjlist[v].data << "：";
        if (D[v] == INT_MAX) {
            cout << "无路径" << endl;
            continue;
        }
        cout << "长度=" << D[v] << "，路径：";
        for (int w = 0; w < G.vexnum; w++) {
            if (P[v][w] == true) {
                cout << G.adjlist[w].data << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    ALGraph G;
    CreateALGraph(G);
    int v0;
    cout << "\n请输入源点的下标：";
    cin >> v0;
    int D[MAXVEX];
    bool P[MAXVEX][MAXVEX];
    Dijkstra(G, v0, D, P);
    PrintPath(G, v0, D, P);
    return 0;
}