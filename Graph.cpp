#include<stdio.h>
#include<stdlib.h>
#define MAXNUM 65536
#define MAXN 128
typedef char VexType;

typedef struct{
	VexType vex[MAXN];
	int arcs[MAXN][MAXN];
	int vexnum,arcnum;
}ABGraph;
typedef struct QNode{
    char data;
    struct QNode *next;
}QNode,*Queue;
typedef struct{
    Queue front;
    Queue rear;
}LinkQueue;
int visited[MAXN];

void Init_Queue(LinkQueue *q){
    q->front = q->rear = (Queue)malloc(sizeof(QNode));
    q->front->next = NULL;
}

void In_Queue(LinkQueue *q,char x){
    Queue p = (Queue)malloc(sizeof(QNode));
    p->data = x;
    p->next = NULL;
    q->rear->next = p;
    q->rear = p;
}
void De_Queue(LinkQueue *q,char &x){
 Queue p;
 if(q->front==q->rear);
 else
 {
  p = q->front->next;
  x = p->data;
  q->front->next = p->next;
  if(q->rear==p)
   q->rear=q->front;
  free(p);
 }
}
int Empty_Queue(LinkQueue *q){
 if(q->front==q->rear)
  return 1;
 else
  return 0;
}
int First_AdjVex(ABGraph *g,int c){
 int j;
 for(j=0;j<g->vexnum;j++)
  if(g->arcs[c][j]<MAXNUM && visited[j]==0)
   return j;
  return -1;
}
int Next_AdjVex(ABGraph *g,int c,int w){
 int j;
 for(j=0;j<g->vexnum;j++)
  if(g->arcs[c][j]<MAXNUM && visited[j]==0)
   return j;
  return -1;
}
int LocateVex(ABGraph *g,char x){
	int i;
	for(i = 0;i < g->vexnum;i++){
		if(g->vex[i] == x)
			return i;
	}
	return -1;
}
int Visit(ABGraph *g,char x){
	int i;
	for(i = 0;i < g->vexnum;i++){
		if(x == g->vex[i])
			printf("%c ",x);
	}
	return LocateVex(g,x);
}
int Creat_Graph(ABGraph *g){
	int i,j,k,x,y,w;
	printf("请输入图的顶点数和边数：\n");
	scanf("%d %d",&g->vexnum,&g->arcnum);
	for(i = 0;i < g->vexnum;i++){
        getchar();
		printf("请输入各顶点的信息：\n");
		scanf("%c",&g->vex[i]);
	}
	for(i = 0;i < g->vexnum;i++)
		for(j = 0;j < g->vexnum;j++)
			g->arcs[i][j] = MAXNUM;
	for(k = 0;k < g->arcnum;k++){
	    getchar();
		printf("请输入图中的一条边连接的两个顶点及权值\n");
		scanf("%c %c %d",&x,&y,&w);
		i = LocateVex(g,x);
		j = LocateVex(g,y);
		g->arcs[i][j] = w;
		g->arcs[j][i] = g->arcs[i][j];
	}
	return 1;
}
void DFS_Graph(ABGraph *g,char x){
	int i,v;
	v = Visit(g,x);
	visited[v] = 1;
	for(i = 0;i <g->vexnum;i++){
		if((g->arcs[v][i]) < MAXNUM && (!visited[i]))
		DFS_Graph(g,g->vex[i]);
	}
}
void BFS_Graph(ABGraph *g,char v){
 int c,w,i;
 char u;
 LinkQueue *Q ;
 c = Visit(g,v);
 visited[c] = 1;
 Init_Queue(Q);
 In_Queue(Q,v);
 while(!Empty_Queue(Q)){
  De_Queue(Q,u);
  c = LocateVex(g,u);
  for(w=First_AdjVex(g,c);w>=0;w=Next_AdjVex(g,c,w))
  {
   if(!visited[w]){
    i = Visit(g,g->vex[w]);
    visited[i] = 1;
    In_Queue(Q,g->vex[w]);
   }
  }
 }
}
int main(){
	ABGraph *g = (ABGraph *)malloc(sizeof(ABGraph));
	char x;
	for(int i = 0;i < g->vexnum;i++)
		visited[i] = 0;
	Creat_Graph(g);
	getchar();
	printf("请输入要开始搜索的顶点：\n");
	scanf("%c",&x);
	//DFS_Graph(g,x);
	BFS_Graph(g,x);
	return 0;
}

