#include <iostream>
#include <cstdlib>
using namespace std;

typedef int ElemType;
typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;
//创建链表
LinkList Initlist(int n)
{
    LinkList head = (LinkList)malloc(sizeof(LNode));
    head->next = NULL;//避免野指针
    LinkList cur = head;
    for(int i = 0; i < n; i++)
    {
        LinkList node = (LinkList)malloc(sizeof(LNode));
        node->data = i + 1;
        node->next = NULL;
        cur->next = node;
        cur = node;
    }
    cur->next = head->next;
    return head;
}
//删除结点
LinkList Deletelist(LinkList &L)
{
    LinkList p;
    p = L->next;
    L->next = p->next;
    free(p);
    return L;
}

int main()
{
    int n, k, m;
    cin>>n>>k>>m;
    //特判
    if(n==1){
        cout<<"剩余最后一人的位置为："<<1<<endl;
        return 0;
    }
    if(n <= 0||k > n||m <= 0){
        cout<<"输入结果错误"<<endl;
        return 0;
    }
    
    LinkList L = Initlist(n);
    for(int i = 1; i <= k; i++)
    {
        L = L->next;
    }
    int count = 1;
    while(L->next!=L)
    {
        
        if(count == m - 1)
        {
            Deletelist(L);
            count = 0;
        }
        else{
            L = L->next;
            count++;
        }
    }
    int pos = L->data;
    cout<<"剩余最后一人的位置为："<<pos<<endl;
    return 0;
}