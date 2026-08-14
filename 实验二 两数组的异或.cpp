"""
已知两个线性表，求两个线性表的异或结果
"""
#include<iostream>
#include<stdlib.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define OVERFLOW -2
#define OK 1
#define ERROR -1
using namespace std;

typedef int ElemType;
typedef int Status;
typedef struct
{
    ElemType *elem;      //�洢�ռ��ַ
    int length;          //��ǰ����
    int listsize;        //��ǰ����Ĵ洢����
}SqList;

// ����һ���յ����Ա�L
Status InitList_Sq(SqList &L)
{
    L.elem = (ElemType * )malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!L.elem) exit(OVERFLOW);
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

// ��˳���L�ĵ�i��λ�ò���Ԫ��e
Status ListInsert_Sq(SqList &L, int i, ElemType e)
{
    if(i < 1 || i > L.length + 1) return ERROR;  // ����ԭ����ı߽��жϴ���
    if(L.length >= L.listsize)
    {
        ElemType *newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if(!newbase) exit(OVERFLOW);
        L.elem = newbase;
        L.listsize += LISTINCREMENT;
    }
    ElemType *q = &(L.elem[i - 1]);
    for(ElemType* p = &(L.elem[L.length - 1]); p >= q; --p)
    {
        *(p + 1) = *p;
    }
    *q = e;
    ++L.length;
    return OK;
}

// �ж�Ԫ��e�Ƿ���˳���L�д���
Status ElemExist(SqList L, ElemType e)
{
    for(int i = 0; i < L.length; i++)
    {
        if(L.elem[i] == e)
            return OK;  // Ԫ�ش���
    }
    return ERROR;  // Ԫ�ز�����
}

// ������˳�������򼯣��������C
Status ListXor_Sq(SqList A, SqList B, SqList &C)
{
    // ��ʼ�������
    if(InitList_Sq(C) != OK)
        return ERROR;
    
    // ��A�в���B�е�Ԫ�ز���C
    for(int i = 0; i < A.length; i++)
    {
        if(ElemExist(B, A.elem[i]) == ERROR)
        {
            if(ListInsert_Sq(C, C.length + 1, A.elem[i]) != OK)
                return ERROR;
        }
    }
    
    // ��B�в���A�е�Ԫ�ز���C
    for(int i = 0; i < B.length; i++)
    {
        if(ElemExist(A, B.elem[i]) == ERROR)
        {
            if(ListInsert_Sq(C, C.length + 1, B.elem[i]) != OK)
                return ERROR;
        }
    }
    
    return OK;
}

// ��ӡ˳���Ԫ��
void PrintList_Sq(SqList L)
{
    for(int i = 0; i < L.length; i++)
    {
        cout << L.elem[i] << " ";
    }
    cout << endl;
}

// ���Ժ���
int main()
{
    SqList A, B, C;
    InitList_Sq(A);
    InitList_Sq(B);
    int a[] = {3, 5, 8, 11};
    int b[] = {2, 6, 8, 9, 11, 15, 20};
    
    // ��A������Ԫ��
    for(int i = 0; i < 4; i++)
    {
        ListInsert_Sq(A, i+1, a[i]);
    }
    
    // ��B������Ԫ��
    for(int i = 0; i < 7; i++)
    {
        ListInsert_Sq(B, i+1, b[i]);
    }
    // �����
    if(ListXor_Sq(A, B, C) == OK)
    {
        cout << "�����: ";
        PrintList_Sq(C); 
    }
    else
    {
        cout << "������ʧ��" << endl;
    }
    
    // �ͷ��ڴ�
    free(A.elem);
    free(B.elem);
    free(C.elem);
    
    return 0;
}
