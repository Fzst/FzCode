#include<stdio.h>
#define MAXSIZE 255//表中元素最大个数

typedef int Elemtype;
typedef struct
{
    Elemtype data[MAXSIZE];
    int length;//表中元素个数
}SeqList;

int Init_List(SeqList *L);//初始化顺序表
int Insert_List(SeqList *L,int l,int x);//插入元素
Elemtype Find_Locaion(SeqList *L,int l);//按位置查找
int Find_Elem(SeqList *L,int x);//按元素值查找
int Empty_List(SeqList *L);//判断顺序表是否为空
int Length_List(SeqList *L);//求表长
int Del_List(SeqList *L,int x);//删除元素
int Modify_List(SeqList *L,int l,int x);//修改元素
void Print_List(SeqList *L);//遍历顺序表

int Init_List(SeqList *L)
{
    L->length = 0;
}

int Insert_List(SeqList *L,int l,int x)
{
    int i;
    if(L->length > MAXSIZE)
    {
        printf("插入失败,表中元素已满。\n");
        return 0;
    }
    if(l < 0 || l > L->length)
    {
        printf("插入的位置有误！\n");
        return 0;
    }
    for(i =  L->length;i > l;i--)
    {
        L->data[i] = L->data[i-1];//表中元素
    }
    L->data[l] = x;
    L->length++;
    return 1;

}

Elemtype Find_Locaion(SeqList *L,int l)
{
     if(l < 0 || l > L->length)
    {
        printf("插入的位置有误！\n");
        return 0;
    }
    return L->data[l];
}

int Empty_List(SeqList *L)
{
    if(L->length == 0)
        return 1;
    else
        return 0;
}

int Length_List(SeqList *L)
{
    return L->length;
}

int Find_Elem(SeqList *L,int x)
{
    int i;
    for(i = 0;i < L->length;i++)
    {
        if(L->data[i] == x)
            return i;
    }
    return -1;
}

int Del_List(SeqList *L,int x)
{
    int l = Find_Elem(L,x);//找到待删元素的位置
    for(int i = l+1;i < L->length;i++)
    {
        L->data[i-1] = L->data[i];//元素依次向前移一位
    }
    L->length--;
    return 1;
}

int Modify_List(SeqList *L,int l,int x)
{
    if(l < 0 || l > L->length)
    {
        printf("修改的位置有误！\n");
        return 0;
    }
    L->data[l] = x;
    return 1;
}

void Print_List(SeqList *L)
{
     for(int i = 0;i < L->length;i++)
    {
        printf("%d\n",L->data[i]);
    }
}

int main()
{
    SeqList L;
    int i;
    int k,m;
    Init_List(&L);
    Insert_List(&L,0,1);
    Insert_List(&L,1,2);
    Insert_List(&L,2,3);
    Insert_List(&L,3,4);
    Insert_List(&L,4,5);
    k = Empty_List(&L);
    m = Length_List(&L);
    printf("%d %d\n",k,m);
    Print_List(&L);
    return 0;
}

