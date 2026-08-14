#include <iostream>
#include <climits>
#define MAXVEX 100
using namespace std;

// 边节点结构
typedef struct ArcNode {
    int adjvex;
    int weight;
    struct ArcNode* nextarc;
} ArcNode;

// 顶点节点结构
typedef struct VNode {
    int data;
    ArcNode* firstarc;
} VNode;

// 邻接链表表示的图
typedef struct {
    VNode adjlist[MAXVEX];
    int vexnum, arcnum;
} ALGraph;

// 创建邻接链表
void CreateALGraph(ALGraph &G) {
    cin >> G.vexnum >> G.arcnum;

    for (int i = 0; i < G.vexnum; i++) {
        cin >> G.adjlist[i].data;
        G.adjlist[i].firstarc = NULL;
    }

    for (int i = 0; i < G.arcnum; i++) {
        int a, b, w;
        cin >> a >> b >> w;

        int x = -1, y = -1;
        for (int k = 0; k < G.vexnum; k++) {
            if (G.adjlist[k].data == a) x = k;
            if (G.adjlist[k].data == b) y = k;
        }

        if (x != -1 && y != -1) {
            ArcNode* p = new ArcNode;
            p->adjvex = y;
            p->weight = w;
            p->nextarc = G.adjlist[x].firstarc;
            G.adjlist[x].firstarc = p;
        }
    }
}

// Floyd算法
void Floyd(ALGraph G, int dist[MAXVEX][MAXVEX], int path[MAXVEX][MAXVEX]) {
    int n = G.vexnum;

    // 初始化dist和path
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) { //顶点自身到自身的距离为0，自身无前驱，标记为-1
                dist[i][j] = 0;
                path[i][j] = -1;
            } else { //初始化距离为无穷大，初始无前驱
                dist[i][j] = INT_MAX;
                path[i][j] = -1;
            }
        }
    }

    // 从邻接表填充直接边权
    for (int i = 0; i < n; i++) {
        ArcNode* p = G.adjlist[i].firstarc; // 取顶点i的第一条边
        while (p != NULL) {
            int j = p->adjvex;
            dist[i][j] = p->weight;
            path[i][j] = i; // j的前驱是i
            p = p->nextarc; // 遍历下一条边
        }
    }

    // 核心迭代
    for (int k = 0; k < n; k++) {// 中间顶点
        for (int i = 0; i < n; i++) {// 起点
            for (int j = 0; j < n; j++) {// 终点
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }
}

// 打印路径
void PrintPath(int path[MAXVEX][MAXVEX], ALGraph G, int i, int j) {
    if (path[i][j] == -1) {
        cout << G.adjlist[i].data;
        if (i != j) cout << " " << G.adjlist[j].data;
        return;
    }
    PrintPath(path, G, i, path[i][j]);
    cout << " " << G.adjlist[j].data;
}

// 输出所有路径
void PrintAllPaths(ALGraph G, int dist[MAXVEX][MAXVEX], int path[MAXVEX][MAXVEX]) {
    int n = G.vexnum;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            cout << G.adjlist[i].data << "到" << G.adjlist[j].data << "：";
            if (dist[i][j] == INT_MAX) {
                cout << "无路径" << endl;
            } else {
                cout << "长度=" << dist[i][j] << "，路径：";
                PrintPath(path, G, i, j);
                cout << endl;
            }
        }
    }
}

int main() {
    ALGraph G;
    CreateALGraph(G);

    int dist[MAXVEX][MAXVEX];
    int path[MAXVEX][MAXVEX];

    Floyd(G, dist, path);
    PrintAllPaths(G, dist, path);

    return 0;
}