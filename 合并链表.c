#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
	int data;
	struct node *next;
}LNode,*LinkList;


LinkList creat_linklist2();
void output(LinkList H);
void List_Merge(LinkList la,LinkList lb,LinkList &lc);


int main()
{
	int m=0;
	LinkList la;
	LinkList lb;
	LinkList lc = la;
	LNode *s,*r;
	printf("请输入信息:\n");
	la = creat_linklist2();
	lb = creat_linklist2();
	output(la);
	output(lb);  
    List_Merge(la,lb,lc);
	output(lc);
	return 0;
}
void List_Merge(LinkList la,LinkList lb,LinkList &lc){

    LinkList pa,pb,pc;

	pa = la->next;

    pb = lb->next;

    lc = pc = la;

    while(pa && pb){

    pc->next = pa;

    pc = pa;

    pa = pa->next;

    pc->next = pb;

    pc = pb;

    pb = pb->next;

}

    pc->next = pa ? pa : pb;
	//output(lc); 
//	return lc;
    free(lb);

}
 LinkList creat_linklist2()
{
	LNode *H=(LNode *)malloc(sizeof(LNode));
	LNode *r,*s;
	r=H;
	int i;
	scanf("%d",&i);
	while(i!=-1)
	{
		s=(LNode *)malloc(sizeof(LNode));
		s->data=i;
		r->next=s;
		r=s;
		scanf("%d",&i);
	}
	r->next=NULL;
	return H;	
}

void output(LinkList H)
{
	node *r;
	r=H->next;
	printf("信息如下:\n"); 
	while(r!=NULL)
	{
		printf("%d ",r->data);
		r=r->next;
	}
 } 
 