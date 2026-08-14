#include<iostream>
#include<cstdlib>
using namespace std;

typedef int Elemtype;
typedef struct LNode
{
    Elemtype c;
    Elemtype e;
    LNode *next;
}LNode, *Ploy;

//向多项式中加入元素
Ploy Attach(Elemtype c, Elemtype e, Ploy &phead)
{
    Ploy newnode = (Ploy)malloc(sizeof(LNode));
    newnode->next = NULL; 
    newnode->c = c;
    newnode->e = e;
    phead->next = newnode;
    phead = phead->next;
    return phead;
}

//读入多项式
Ploy readploy()
{
    int N;
    cin>>N;
    Ploy head = (Ploy)malloc(sizeof(LNode));
    head->next = NULL;
    Ploy cur = head;
    Elemtype c, e;
    while(N--)
    {
        cin>>c>>e;
        Attach(c, e, cur);
    }
    return head;
}

//释放空间
void destroyploy(Ploy &head)
{
    while(head)
    {
        Ploy t = head;
        head = head->next;
        free(t);
    }
}

//输出多项式
void Output(Ploy &head)
{
    if(head->next == NULL)
    {
        cout<<0;
        return ;
    }
    Ploy cur = head->next;
    if(cur->c != 0)
    {
        if(cur->c == -1)cout<<'-';
        else if(cur->c != 1)cout<<cur->c;
        if(cur->e > 1)cout<<"x^"<<cur->e;
        else if(cur->e == 1)cout<<'x';
        else if(cur->e < 0)cout<<"x^"<<'('<<cur->e<<')';
    }
    cur = cur->next;
    while(cur)
    {
        if(cur->c == 0)
        {
            cur = cur->next;
            continue;
        }
        else if(cur->c > 1)cout<<'+'<<cur->c;
        else if(cur->c == -1)cout<<'-';
        else if(cur->c != 1)cout<<cur->c;
        if(cur->e > 1)cout<<"x^"<<cur->e;
        else if(cur->e == 1)cout<<'x';
        else if(cur->e < 0)cout<<"x^"<<'('<<cur->e<<')';
        cur = cur->next;
    }
}

//两多项式相加，对其中一个多项式进行修改
void fun(Ploy &pa, Ploy &pb)
{
    Ploy late = pa;//快慢指针
    Ploy curA = pa->next;
    Ploy curB = pb->next;
    while(curB)
    {
        if (curA == NULL)
        {
            late->next = curB;
            curB = NULL;
            break;
        }
        if(curA->e == curB->e)
        {
            curA->c += curB->c;
            curA = curA->next;
            curB = curB->next;
        }
        else if(curB->e < curA->e)
        {
            curA = curA->next;
            late = late->next;
        }
        else
        {
            Ploy t = curB;
            curB = curB->next;
            late->next = t;
            t->next = curA;
            late = t;
        }
    }
}
int main()
{
    Ploy pa = readploy();
    cout<<"第一个多项式："<<endl;
    Output(pa);
    cout<<endl;
    Ploy pb = readploy();
    cout<<"第二个多项式"<<endl;
    Output(pb);
    cout<<endl;
    fun(pa, pb);
    cout<<"相加后的多项式："<<endl;
    Output(pa);
    destroyploy(pa);
    destroyploy(pb);
    return 0;
}