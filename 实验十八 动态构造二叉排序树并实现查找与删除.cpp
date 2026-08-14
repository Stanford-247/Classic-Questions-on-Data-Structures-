#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct BSTNode{
    int data;
    struct BSTNode *lchild;
    struct BSTNode *rchild;
}BSTNode, *BSTree;

//动态插入节点
void InsertBST(BSTree &T, int key)
{
    if(T == NULL)
    {
        T = (BSTree)malloc(sizeof(BSTNode));
        T->data = key;
        T->lchild = T->rchild = NULL;
    }
    if(key < T->data)
    {
        InsertBST(T->lchild, key);
    }
    else if(key > T->data)
    {
        InsertBST(T->rchild, key);
    }
}

//构建二叉排序树
void CreateBST(BSTree &T, int a[], int n)
{
    T = NULL;
    for(int i = 0; i < n;i++)
    {
        InsertBST(T, a[i]);
    }
}

//查找指定节点
BSTree SearchBST(BSTree T, int key) {
    if (T == NULL || T->data == key) {
        return T;
    }
    if (key < T->data) {
        return SearchBST(T->lchild, key);
    }
    else {
        return SearchBST(T->rchild, key);
    }
}

// 找到右子树中值最小的节点
BSTNode* FindMin(BSTree T) {
    while (T->lchild != NULL) {
        T = T->lchild;
    }
    return T;
}

// 删除指定值的节点
bool DeleteBST(BSTree &T, int key) {
    if (T == NULL) {
        return false; 
    }
    if (key == T->data) {
        // 待删节点是叶子节点
        if (T->lchild == NULL && T->rchild == NULL) {
            free(T);
            T = NULL; 
        }
        // 待删节点只有右孩子
        else if (T->lchild == NULL) {
            BSTNode *temp = T;
            T = T->rchild; // 右孩子接替当前节点
            free(temp);
        }
        // 待删节点只有左孩子
        else if (T->rchild == NULL) {
            BSTNode *temp = T;
            T = T->lchild; // 左孩子接替当前节点
            free(temp);
        }
        //待删节点有左右两个孩子
        else {
            // 找右子树最小值节点
            BSTNode *minNode = FindMin(T->rchild);
            T->data = minNode->data; // 替换待删节点值
            DeleteBST(T->rchild, minNode->data); // 删除最小值节点
        }
        return true;
    }
    // 未找到：递归查找左/右子树
    else if (key < T->data) {
        return DeleteBST(T->lchild, key);
    }
    else {
        return DeleteBST(T->rchild, key);
    }
}

void InOrderTraverse(BSTree T) {
    if (T != NULL) {
        InOrderTraverse(T->lchild);
        cout << T->data << " ";
        InOrderTraverse(T->rchild);
    }
}

int main() {
    int arr[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(arr) / sizeof(arr[0]);
    BSTree T;
    CreateBST(T, arr, n);
    cout << "数组排序后的结果为：";
    InOrderTraverse(T);
    cout << endl;
    //  查找节点
    int searchKey = 40;
    BSTNode *res = SearchBST(T, searchKey);
    if (res) {
        cout << "找到节点：" << res->data << endl;
    } else {
        cout << "未找到节点：" << searchKey << endl;
    }
    // 删除节点
    int delKey1 = 20;
    if (DeleteBST(T, delKey1)) {
        cout << "删除节点" << delKey1 << "：";
        InOrderTraverse(T);
        cout << endl;
    }
    int delKey2 = 50;
    if (DeleteBST(T, delKey2)) {
        cout << "删除节点" << delKey2 << "：";
        InOrderTraverse(T);
        cout << endl;
    }

    return 0;
}