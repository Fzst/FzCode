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

int visited[MAXN];
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
	printf("������ͼ�Ķ������ͱ�����\n");
	scanf("%d %d",&g->vexnum,&g->arcnum);
	for(i = 0;i < g->vexnum;i++){
        getchar();
		printf("��������������Ϣ��\n");
		scanf("%c",&g->vex[i]);
	}
	for(i = 0;i < g->vexnum;i++)
		for(j = 0;j < g->vexnum;j++)
			g->arcs[i][j] = MAXNUM;
	for(k = 0;k < g->arcnum;k++){
	    getchar();
		printf("������ͼ�е�һ�������ӵ��������㼰Ȩֵ\n");
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
int main(){
	ABGraph *g = (ABGraph *)malloc(sizeof(ABGraph));
	char x;
	for(int i = 0;i < g->vexnum;i++)
		visited[i] = 0;
	Creat_Graph(g);
	getchar(); 
	printf("������Ҫ��ʼ�����Ķ��㣺\n");
	scanf("%c",&x);
	DFS_Graph(g,x);
	return 0;
}

