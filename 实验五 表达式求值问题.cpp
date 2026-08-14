#include<iostream>
#include<cstdlib>
#include<cctype>
#define STACK_INIT_SIZE 100//存储空间初始分配量
#define STACKINCREMENT 10//存储空间分配增量
#define OK 1
#define ERROR -1
#define OVERFLOW -2
using namespace std;
typedef int Status;
typedef char SElemType;
typedef int OperandType;
typedef struct{
    SElemType *base;
    SElemType *top;
    int stacksize;
}OptrStack;//运算符栈
typedef struct{
    OperandType *base;
    OperandType *top;
    int stacksize;
}OpndStack;//运算数栈

Status InitOpndStack(OpndStack &S){
    S.base = (OperandType*)malloc(STACK_INIT_SIZE * sizeof(OperandType));//初始分配空间乘上结构体的空间大小
    if(!S.base)exit(OVERFLOW);//空间分配失败，结束程序
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}

Status InitOptrStack(OptrStack &S){
    S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!S.base)exit(OVERFLOW);
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}

Status Push(OptrStack &S, SElemType e){
    if(S.top - S.base >= S.stacksize){
        S.base = (SElemType*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));//以原栈底为基础重新分配空间
        if(!S.base)exit(OVERFLOW);
        S.top = S.base + S.stacksize;//更新栈顶指针，此时的栈顶指针位于原栈顶的位置
        S.stacksize += STACKINCREMENT;//更新栈的最大容量
    }
    *S.top++ = e;
    return OK;
}//向栈中放入新元素

Status Push(OpndStack &S, OperandType e){
    if(S.top - S.base >= S.stacksize){//栈中已存储元素的个数是否超过栈内的最大空间
        S.base = (OperandType*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(OperandType));
        if(!S.base)exit(OVERFLOW);
        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return OK;
}

Status Pop(OpndStack &S, OperandType &e){
    if(S.top == S.base)return ERROR;
    e = *--S.top;
    return OK;
}//删除栈顶元素并返回

Status Pop(OptrStack &S, SElemType &e){
    if(S.top == S.base)return ERROR;
    e = *--S.top;
    return OK;
}

Status GetTop(OpndStack &S, OperandType &e){
    if(S.top == S.base) return ERROR;
    e = *(S.top - 1);
    return OK;
}//用e返回栈顶元素

Status GetTop(OptrStack &S, SElemType &e){
    if(S.top == S.base) return ERROR;
    e = *(S.top - 1);
    return OK;
}

char Precede(char op1, char op2){
    char precedence[7][7] = {
        {'>', '>', '<', '<', '<', '>', '>'},  // op1为+时
        {'>', '>', '<', '<', '<', '>', '>'},  // op1为-时
        {'>', '>', '>', '>', '<', '>', '>'},  // op1为*时
        {'>', '>', '>', '>', '<', '>', '>'},  // op1为/时
        {'<', '<', '<', '<', '<', '=', ' '},  // op1为(时
        {'>', '>', '>', '>', ' ', '>', ' '},  // op1为)时
        {'<', '<', '<', '<', '<', ' ', '='}   // op1为#时
    };
    int i, j;
    switch(op1) {
        case '+': i=0; break;
        case '-': i=1; break;
        case '*': i=2; break;
        case '/': i=3; break;
        case '(': i=4; break;
        case ')': i=5; break;
        case '#': i=6; break;
        default:  return ' ';
    }
    switch(op2) {
        case '+': j=0; break;
        case '-': j=1; break;
        case '*': j=2; break;
        case '/': j=3; break;
        case '(': j=4; break;
        case ')': j=5; break;
        case '#': j=6; break;
        default:  return ' ';
    }
    return precedence[i][j];
}//判断运算符优先级

OperandType Operate(OperandType a, char op, OperandType b){
    switch(op){
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if(b == 0){  // 处理除零错误
                cout << "错误：除数不能为0！" << endl;
                exit(ERROR);
            }
            return a / b;  // 整数除法
        default: return 0;
    }
}//运算操作

OperandType EvaluateExpression(){
    OptrStack OPTR;
    OpndStack OPND;
    InitOptrStack(OPTR); //创建运算符栈
    Push(OPTR, '#');
    InitOpndStack(OPND); //创建运算数栈
    char c;
    c = getchar();
    SElemType top_op, theta, x;
    OperandType a, b, num;
    while(c!='#' || (GetTop(OPTR, top_op) == OK && top_op != '#')){
        if(isdigit(c)){//判断是否是数字
            num = 0;
            while(isdigit(c)){//多位数
                num = num * 10 + (c - '0');//转化
                c = getchar();
            }
            Push(OPND, num);
        }
        else{
            GetTop(OPTR, top_op);
            switch(Precede(top_op, c)){
                case '<':
                    Push(OPTR, c);
                    c = getchar();
                    break;
                case '=':
                    Pop(OPTR, x);
                    c = getchar();
                    break;
                case '>':
                    Pop(OPTR, theta);
                    Pop(OPND, b);
                    Pop(OPND, a);
                    Push(OPND, (SElemType)Operate(a, theta, b));
                    break;
            }
        }
    }
    OperandType result;
    GetTop(OPND, result);
    return (OperandType)result;
}

int main(){
    cout << "请输入中缀表达式（以#结束）：" << endl;
    OperandType result = EvaluateExpression();
    cout << "计算结果：" << result << endl;
    return 0;
}