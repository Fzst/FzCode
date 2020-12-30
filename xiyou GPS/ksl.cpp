#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
//#include<graphics.h>

#define true 1
#define false 0
#define MAXN 30//表示顶点的最大个数
#define MAXNS 50//数组个数最大值
#define INF 65535//表示极大值

//求所有路径的全局变量
int a = 0;/*全局变量，用来记录每对顶点之间的所有路径的条数*/
int visited[MAXNS];/*全局数组，用来记录各顶点被访问的情况*/
int v[MAXNS];/*全局数组，用来存放路径上的各顶点*/

//求最少中转次数的全局变量
int count2 = 0;
int load[MAXNS] = { 0 }; //路径数组 
int Min = MAXN; //中转最少顶点数最值 
int Ways[MAXNS] = { 0 };//路径数组 


//求最短路径的全局变量
long int Dist[MAXNS];  // 辅助变量存储最短路径长度 
int p[MAXNS][MAXNS];  //起点到终点的路径数组

typedef struct user//创建关于用户信息的结构体 
{
	char name[50];//账号 
	char code[50];//密码 
}User;

typedef struct {//创建关于图的顶点信息的结构体
	char placename[50];
	char intro[255];
	int visited;//访问标志
}Vextype;

typedef struct {//创建邻接矩阵结构体
	int arcs[MAXN][MAXN];//边和顶点的对应关系
	Vextype nums[MAXN];//顶点数组
	int vexnum;//顶点数目
	int arcnum;//边的数目
}AdjGraph;

void Register();//用户注册
void login(AdjGraph G);//用户登录
int bijiao(User signin);
void Tour();//游客登录
void Admin();//管理员登录
void Admin_Meau(AdjGraph G);//管理员菜单

void Append_Data(AdjGraph* G);//添加信息
void Delete_Data(AdjGraph* G);//删除信息
//void Map_Out1();//校园实景图展示
void Print_Map();//打印出手绘平面图
void Display_Place(AdjGraph* G);//地点编号与名称显示


void Map_toFile();//将地图写入文件
void Info_Place_tofile();//将地点的名称与介绍写入文件
void Adj_tofile();//将邻接矩阵信息写入文件


void Creat_Graph(AdjGraph* G);//创建图
void Search(AdjGraph G);//地点信息查询
void Search_Load(AdjGraph G);//问路查询

void path(AdjGraph* G, int i, int j, int k);//所有路径
void Visited(AdjGraph* G);

void Simple_Load(AdjGraph G);//所有简单路径
void DFS(AdjGraph* G, int s, int e);//中转最少
void Tansit_Load(AdjGraph G);//中转最少
void Shortest_Load(AdjGraph G);//最短路径
void ShortestPath_DIJ(AdjGraph* G, int v0);
void output(AdjGraph* G, int sight1, int sight2);

//注册信息
void Register()
{
	User signin;
	FILE* fp1;
	fp1 = fopen("user.txt", "a+");//用‘a+’方式打开文件，方便后续往文件里写信息 
	if (fp1 == NULL)
	{
		printf("\t打开失败,按任意键退出！\n");
		exit(1);
	}
	printf("\t请输入用户名：\n");
	getchar();
	//fgets(signin.name);
	scanf("%s", signin.name);
	printf("\n");
	if (bijiao(signin) == 0)
	{
		printf("\t对不起，您注册的用户名重复，请重新输入\n");
		getch();
		system("cls");
		Admin();
	}
	else if (bijiao(signin) == 1)
	{
		printf("\t请设置密码：\n");
		//gets(signin.code);
		scanf("%s", signin.code);
		fputs(signin.name, fp1);
		fputs(" ", fp1);
		fputs(signin.code, fp1);
		fputs("\n", fp1);
		fclose(fp1);
		printf("\t\t*****  注册成功，按任意键返回  *****\n");
		getch();
		system("cls");
		Admin();
	}
}


void login(AdjGraph G)
{
	User log;
	FILE* fp1;
	int flag = 0;
	char  p[50];
	//char ch[50];
	char* ch = (char*)malloc(sizeof(char) * 50);
	fp1 = fopen("user.txt", "rt");//用‘rt’方式打开文件，只允许读取数据
	printf("\t请输入用户名：");
	getchar();
	//gets(ch);
	scanf("%s", ch);
	printf("\t请输入密码：");
	char a[20];
	int i = 0;
	while ((p[i] = getch()) != '\r')
	{
		if (p[i] == '\b')//对backspace键的处理 
		{
			printf("\b \b");
			i--;
		}
		else
		{
			printf("*");
			i++;
		}
	}
	p[i] = '\0';
	while (fscanf(fp1, "%s %s", log.name, log.code) != EOF)
	{
		if (strcmp(ch, log.name) == 0 && strcmp(p, log.code) == 0)
		{
			flag = 1;
			break;
		}
		else if (strcmp(ch, log.name) == 0 && strcmp(p, log.code) != 0)
		{
			flag = 0;
			break;
		}
		else if (strcmp(ch, log.name) != 0)
		{
			flag = 2;
			continue;
		}
	}
	if (flag == 1)
	{
		printf("\n");
		printf("登录成功！\n");
		Admin_Meau(G);
	}
	else if (flag == 0)
	{
		printf("\t密码出错！\n");
		getch();
		system("cls");
		Admin();
	}
	else if (flag == 2)
	{
		printf("\t您输入用户名不存在！\n");
		getch();
		system("cls");
		Admin();
	}

}


int bijiao(User signin)
{
	FILE* fp1;
	User member;
	int flag = 2;
	fp1 = fopen("user.txt", "rt");//用‘rt’方式打开文件，只允许读取数据
	if (fp1 == NULL)
	{
		printf("\t输入无效，按任意键返回注册！\n");
		getch();
		system("cls");
		exit(1);
	}
	while (fscanf(fp1, "%s", member.name) != EOF)
	{
		if (strcmp(signin.name, member.name) == 0)
		{
			flag = 0;
			break;
		}
		else if (strcmp(signin.name, member.name) != 0)
		{
			flag = 1;
			continue;
		}
	}
	if (flag == 0)
	{
		return 0;
	}
	else if (flag == 1)
	{
		return 1;
	}
	else if (flag == 2)
	{
		return 1;
	}
}


void Tour() {
	int choice;
	AdjGraph G;
	Creat_Graph(&G);
	while (1) {
		printf("                           \t┏━━━━━━━━━━━━━━━━━━━━┓\n");
		printf("\t\t\t\t┃  1:手绘校园平面图  ┃\n\n");
		printf("\t\t\t\t┃  2:校园实景图      ┃\n\n");
		printf("\t\t\t\t┃  3:地点信息查询    ┃\n\n");
		printf("\t\t\t\t┃  4:问路查询        ┃\n\n");
		printf("\t\t\t\t┃  0:退出            ┃\n\n");
		printf("                           \t┗━━━━━━━━━━━━━━━━━━━━┛\n");
		printf("\t\t\t\t请输入您的选择:\n");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			Print_Map(); break;
		case 2:
			//Map_Out1(); break;
		case 3:
			Search(G); break;
		case 4:
			Search_Load(G); break;
		case 0:
			exit(0); break;
		default:
			printf("输入有误，请重新输入！\n");
			break;
		}
	}
}


void Admin() {
	int choice;
	AdjGraph G;
	system("cls");
	Map_toFile();
	Info_Place_tofile();
	Adj_tofile();
	Creat_Graph(&G);
	printf("\t\t\t\t1:登录\t\t");
	printf("2:注册\n\n");
	printf("\t\t\t\t请输入你的选择");
	while (1) {
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			login(G); break;
		case 2:
			Register(); break;
		default:
			printf("输入有误，请重新输入！\n");
			break;
		}
	}
}

void Admin_Meau(AdjGraph G) {
	int choice;
	while (1) {

		printf("                           \t┏━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
		printf("\t\t\t\t┃  1:手绘校园平面图      ┃\n\n");
		printf("\t\t\t\t┃  2:校园实景图          ┃\n\n");
		printf("\t\t\t\t┃  3:地点信息查询        ┃\n\n");
		printf("\t\t\t\t┃  4:问路查询            ┃\n\n");
		printf("\t\t\t\t┃  5:增加信息            ┃\n\n");
		printf("\t\t\t\t┃  6:删除信息(仅删除路线)┃\n\n");
		printf("\t\t\t\t┃  0:退出                ┃\n\n");
		printf("                           \t┗━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
		printf("\t\t\t\t请输入您的选择:\n");
		scanf("%d", &choice);
		getchar();
		switch (choice) {
		case 1:
			Print_Map(); break;
		case 2:
			//Map_Out1(); break;
		case 3:
			Search(G); break;
		case 4:
			Search_Load(G); break;
		case 5:
			Append_Data(&G); break;
		case 6:
			Delete_Data(&G); break;
		case 0:
			exit(0);
			break;
		default:
			printf("输入有误，请重新输入！\n"); break;
		}
	}
}

void Append_Data(AdjGraph* G) {
	char data[20] = "data.txt";
	char name[30] = "info.txt";
	char adj[30] = "adj.txt";
	//char* name1 = (char*)malloc(sizeof(char)*30);
	//char* info1 = (char*)malloc(sizeof(char)*50);
	char name1[30];
	char info1[50]; 
	int flag = 1;
	int flag1;
	int e,w;
	while (flag == 1) {
		printf("\t\t\t\t请输入要添加的地点名称:\n");
		scanf("%s",name1);
		getchar();
		printf("\t\t\t\t请输入要添加的地点介绍:\n");
		scanf("%s",info1);
		G->vexnum += 1;

		strcpy(G->nums[G->vexnum].placename, name1);
		strcpy(G->nums[G->vexnum].intro, info1);

		FILE* fp;
		fp = fopen(name, "at");
		if (fp == NULL) {
			printf("打开失败!\n");
		}

		fprintf(fp, "%s\n%s", G->nums[G->vexnum].placename, G->nums[G->vexnum].intro);
		fclose(fp);

		FILE* fp1;
		fp1 = fopen(data, "wt");
		if (fp1 == NULL) {
			printf("打开失败!\n");
		}
		fprintf(fp1, "%d\n%d", G->vexnum, G->arcnum);
		fclose(fp1);

		printf("\t\t\t\t添加成功!\n");
		printf("\t\t\t\t是否要为此地点添加新路线:\n");
		printf("\t\t\t\t1:是    0:否\n");
		scanf("%d", &flag1);
		
		if (flag1 == 1) {
			Display_Place(G);
			printf("\t\t\t\t请输入到达地点编号:\n");
			scanf("%d", &e);
			printf("\t\t\t\t请输入两个地点之间的路程:\n");
			scanf("%d", &w);
			G->arcs[G->vexnum][e] = G->arcs[e][G->vexnum] = w;
			FILE* fp3;
			fp3 = fopen(adj, "at");
			if (fp3 == NULL) {
				printf("打开失败!\n");
			}
			fprintf(fp3, "%d %d %d", G->vexnum, e, G->arcs[G->vexnum][e]);
			fclose(fp3);
			G->arcnum += 1;
			fp1 = fopen(data, "wt");
			if (fp1 == NULL) {
				printf("打开失败!\n");
			}
			fprintf(fp1, "%d %d\n", G->vexnum, G->arcnum);
			fclose(fp1);

			printf("添加完成!\n");
			flag1 = 0;
		}
		printf("\t\t\t\t还有要添加的地点吗?\n");
		printf("\t\t\t\t1:是    0:否\n");
		scanf("%d", &flag);
	}
}
void Delete_Data(AdjGraph* G) {
	char data[20] = "data.txt";
	char adj[30] = "adj.txt";
	int flag = 1,s,e;
	while (flag == 1) {
		Display_Place(G);
		printf("请输入要删除路线的起点:\n");
		scanf("%d", &s);

		printf("请输入要删除路线的终点:\n");
		scanf("%d", &e);

		G->arcs[s][e] = G->arcs[e][s] = INF;

		FILE* fp3;
		fp3 = fopen(adj, "at");
		if (fp3 == NULL) {
			printf("打开失败!\n");
		}
		fprintf(fp3, "%d %d %d", s, e, G->arcs[s][e]);
		fclose(fp3);

		G->arcnum -= 1;
		FILE* fp1;
		fp1 = fopen(data, "wt");
		if (fp1 == NULL) {
			printf("打开失败!\n");
		}

		fprintf(fp1, "%d\n%d", G->vexnum, G->arcnum);
		fclose(fp1);
		printf("\t\t\t\t删除成功!\n");
		printf("\t\t\t\t还有要删除的路线吗?\n");
		printf("\t\t\t\t1:是    0:否\n");
		scanf("%d", &flag);
	}

}
/*void Map_Out1() {
	IMAGE image1;
	initgraph(800, 800);
	loadimage(&image1, L"map.jpg", 780, 780);
	putimage(10, 10, &image1);
	system("pause");
	closegraph();
}*/ 


void Print_Map() {
	printf("|--------------------------------------------------------------------------------------------------------|\n");
	printf("|                                ☆西安邮电大学长安校园地图 ☆                                           |\n");
	printf("|--------------------------------------------------------------------------------------------------------|\n");
	printf("|                                 北门                                                                   |\n");
	printf("|                                 |                                                                      |\n");
	printf("|                                 |                           东区大门=======120=======逸夫楼            |\n");
	printf("|                                150                                                    |                |\n");
	printf("|                                 |                                                     |                |\n");
	printf("|                                 |                                                    130               |\n");
	printf("|                                 |                                                     |                |\n");
	printf("|                 |=====230====水煮鸽子                                                 |                |\n");
	printf("|                 |               |                                                  东区公寓            |\n");
	printf("|                 |               |                                                     |                |\n");
	printf("|            基础教学楼           |                                                     240              |\n");
	printf("|                 |               |                                                     |                |\n");
	printf("|                 |               |                                                     |                |\n");
	printf("|                 |               |                                                     |                |\n");
	printf("|                200             450                                                    |                |\n");
	printf("|                 |               |                                                   东升苑             |\n");
	printf("|                 |               |                                                     |                |\n");
	printf("|                 |               |                                                     |                |\n");
	printf("|                 |             图书馆                                                 500               |\n");
	printf("|                 |               |                                                     |                |\n");
	printf("|                 |               |                                                     |                |\n");
	printf("|                 |               |=====================================================|                |\n");
	printf("|                 |              400               |||   西邮桥   |||                   |                |\n");
	printf("|  医务室=========|               |=====================================================|                |\n");
	printf("|                                 |                                                                      |\n");
	printf("|                               体育馆                                                                   |\n");
	printf("|                                 |                                                                      |\n");
	printf("|                                330                                                                     |\n");
	printf("|                                 |                                                                      |\n");
	printf("|                              旭日苑                                                                    |\n");
	printf("|                                 |                                                                      |\n");
	printf("|                                210                                                                     |\n");
	printf("|                                 |                                                                      |\n");
	printf("|                             西区公寓                                                                   |\n");
	printf("|--------------------------------------------------------------------------------------------------------|\n");
}


void Display_Place(AdjGraph* G) {
	int i;
	system("cls");
	printf("\t\t\t\t\t\t        ★西安邮电大学★\n");
	printf("\t\t\t\t\t\t__________________________________\n");
	printf("\t\t\t\t\t\t编号\t\t\t名称\n");
	for (i = 1; i <= G->vexnum; i++) {
		printf("\t\t\t\t\t\t<%d>\t\t\t%s\n", i, G->nums[i].placename);
	}
}

void Map_toFile() {
	char map[20] = "map.txt";
	FILE* fp;
	fp = fopen(map, "wt");
	if (fp == NULL) {
		printf("打开文件失败！");
		return;
	}
	fprintf(fp, "|--------------------------------------------------------------------------------------------------------|\n");
	fprintf(fp, "|                                ☆西安邮电大学长安校园地图 ☆                                           |\n");
	fprintf(fp, "|--------------------------------------------------------------------------------------------------------|\n");
	fprintf(fp, "|                                 北门                                                                   |\n");
	fprintf(fp, "|                                 |                                                                      |\n");
	fprintf(fp, "|                                 |                           东区大门=======120=======逸夫楼            |\n");
	fprintf(fp, "|                                150                                                    |                |\n");
	fprintf(fp, "|                                 |                                                     |                |\n");
	fprintf(fp, "|                                 |                                                    130               |\n");
	fprintf(fp, "|                                 |                                                     |                |\n");
	fprintf(fp, "|                 |=====230====水煮鸽子                                                 |                |\n");
	fprintf(fp, "|                 |               |                                                  东区公寓            |\n");
	fprintf(fp, "|                 |               |                                                     |                |\n");
	fprintf(fp, "|            基础教学楼           |                                                     240              |\n");
	fprintf(fp, "|                 |               |                                                     |                |\n");
	fprintf(fp, "|                 |               |                                                     |                |\n");
	fprintf(fp, "|                 |               |                                                     |                |\n");
	fprintf(fp, "|                200             450                                                    |                |\n");
	fprintf(fp, "|                 |               |                                                   东升苑             |\n");
	fprintf(fp, "|                 |               |                                                     |                |\n");
	fprintf(fp, "|                 |               |                                                     |                |\n");
	fprintf(fp, "|                 |             图书馆                                                 500               |\n");
	fprintf(fp, "|                 |               |                                                     |                |\n");
	fprintf(fp, "|                 |               |                                                     |                |\n");
	fprintf(fp, "|                 |               |=====================================================|                |\n");
	fprintf(fp, "|                 |              400               |||   西邮桥   |||                   |                |\n");
	fprintf(fp, "|  医务室=========|               |=====================================================|                |\n");
	fprintf(fp, "|                                 |                                                                      |\n");
	fprintf(fp, "|                               体育馆                                                                   |\n");
	fprintf(fp, "|                                 |                                                                      |\n");
	fprintf(fp, "|                                330                                                                     |\n");
	fprintf(fp, "|                                 |                                                                      |\n");
	fprintf(fp, "|                              旭日苑                                                                    |\n");
	fprintf(fp, "|                                 |                                                                      |\n");
	fprintf(fp, "|                                210                                                                     |\n");
	fprintf(fp, "|                                 |                                                                      |\n");
	fprintf(fp, "|                             西区公寓          	                                                      |\n");
	fprintf(fp, "|--------------------------------------------------------------------------------------------------------|\n");
	fclose(fp);
}

void Info_Place_tofile() {
	int i;
	char name[30] = "info.txt";
	AdjGraph G;
	FILE* fp;
	fp = fopen(name, "wt");
	if (fp == NULL) {
		printf("打开失败!");
	}

	G.vexnum = 13;

	strcpy(G.nums[1].placename, "医务室");
	strcpy(G.nums[1].intro, "位于西安邮电大学最西边");
	strcpy(G.nums[2].placename, "基础教学楼");
	strcpy(G.nums[2].intro, "西安邮电大学西区学生上课，学习的地方，分为A楼和B楼");
	strcpy(G.nums[3].placename, "水煮鸽子");
	strcpy(G.nums[3].intro, "西安邮电大学喷泉，位于西区北门");
	strcpy(G.nums[4].placename, "北门");
	strcpy(G.nums[4].intro, "西安邮电大学正门");
	strcpy(G.nums[5].placename, "图书馆");
	strcpy(G.nums[5].intro, "西安邮电大学图书馆，藏书丰富，可以供学生借阅");
	strcpy(G.nums[6].placename, "西邮桥");
	strcpy(G.nums[6].intro, "连通西安邮电大学东区和西区的一条通路");
	strcpy(G.nums[7].placename, "体育场");
	strcpy(G.nums[7].intro, "西安邮电大学体育馆，有室内的也有室外的，可供学生们运动与上课");
	strcpy(G.nums[8].placename, "旭日苑");
	strcpy(G.nums[8].intro, "西安邮电大学西区食堂");
	strcpy(G.nums[9].placename, "西区公寓");
	strcpy(G.nums[9].intro, "西安邮电大学西区学生休息，睡觉的地方，位于西安邮电大学最南边");
	strcpy(G.nums[10].placename, "东升苑");
	strcpy(G.nums[10].intro, "西安邮电大学东区食堂");
	strcpy(G.nums[11].placename, "东区公寓");
	strcpy(G.nums[11].intro, "西安邮电大学东区学生休息，睡觉的地方，位于西安邮电大学最东边");
	strcpy(G.nums[12].placename, "逸夫楼");
	strcpy(G.nums[12].intro, "西安邮电大学东区学生上课，学习的地方，有A,B,C,D四个入口");
	strcpy(G.nums[13].placename, "东区大门");
	strcpy(G.nums[13].intro, "西安邮电大学东区正门");

	//把信息存到文件中
	for (i = 1; i <= G.vexnum; i++) {
		fprintf(fp, "%s\n%s\n", G.nums[i].placename, G.nums[i].intro);
	}
	fclose(fp);
}


void Adj_tofile() {
	int i, j;
	char data[20] = "data.txt";
	char Adj[20] = "Adj.txt";
	AdjGraph G;
	FILE* fp;
	fp = fopen(data, "wt");
	if (fp == NULL) {
		printf("打开失败!\n");
		exit(-1);
	}

	FILE* fp1;
	fp1 = fopen(Adj, "wt");
	if (fp1 == NULL) {
		printf("打开失败!\n");
		exit(-1);
	}

	G.vexnum = 13;
	G.arcnum = 21;

	fprintf(fp, "%d %d\n", G.vexnum, G.arcnum);//顶点数与边数写入文件

	for (i = 0; i <= G.vexnum; i++) {//初始化顶点信息
		for (j = 0; j <= G.vexnum; j++) {
			G.arcs[i][j] = INF;
		}
	}

	G.arcs[1][2] = G.arcs[2][1] = 200;//1
	G.arcs[2][3] = G.arcs[3][2] = 230;//2
	G.arcs[3][4] = G.arcs[4][3] = 150;//3
	G.arcs[3][5] = G.arcs[5][3] = 450;//4
	G.arcs[5][6] = G.arcs[6][5] = 400;//5
	G.arcs[6][7] = G.arcs[7][6] = 50;//6
	G.arcs[5][7] = G.arcs[7][5] = 420;//7
	G.arcs[7][8] = G.arcs[8][7] = 330;//8
	G.arcs[8][9] = G.arcs[9][8] = 210;//9
	G.arcs[6][10] = G.arcs[10][6] = 510;//10
	G.arcs[10][11] = G.arcs[11][10] = 230;//11
	G.arcs[11][12] = G.arcs[12][11] = 134;//12
	G.arcs[12][13] = G.arcs[13][12] = 125;//13
	G.arcs[6][9] = G.arcs[9][6] = 600;//14
	G.arcs[1][9] = G.arcs[9][1] = 550;//15
	G.arcs[2][5] = G.arcs[5][2] = 190;//16
	G.arcs[4][13] = G.arcs[13][4] = 800;//17
	G.arcs[3][6] = G.arcs[6][3] = 850;//18
	G.arcs[6][12] = G.arcs[12][6] = 724;//19
	G.arcs[2][8] = G.arcs[8][2] = 470;//20



	for (i = 1; i <= G.vexnum; i++) {//将地点之间的关系以及路程写入文件
		for (j = 1; j <= G.vexnum; j++) {
			if (G.arcs[i][j] != INF && i < j)
				fprintf(fp1, "%d %d %d\n", i, j, G.arcs[i][j]);
		}
	}

	fclose(fp1);//关闭文件
	fclose(fp);
}


void Creat_Graph(AdjGraph* G) {
	int i, j, k, m, w;
	int vexnum1, arcnum1;
	//char* name = (char*)malloc(sizeof(char) * 20);//用来暂存文件中的读取到的地点名称
	//char* intro = (char*)malloc(sizeof(char) * 70);//用来暂存文件中读取到的地点介绍
	char name[20];
	char intro[70];
	FILE* fp1;
	fp1 = fopen("data.txt", "rt");
	if (fp1 == NULL) {
		printf("打开失败!");
		exit(-1);
	}

	FILE* fp2;
	fp2 = fopen("info.txt", "rt");
	if (fp2 == NULL) {
		printf("打开失败!");
		exit(-1);
	}

	FILE* fp;
	fp = fopen("Adj.txt", "rt");
	if (fp == NULL) {
		printf("打开失败!");
		exit(-1);
	}

	fscanf(fp1, "%d %d", &vexnum1, &arcnum1);
	G->vexnum = vexnum1;//顶点数
	G->arcnum = arcnum1;//边数

	for (i = 1; i <= G->vexnum; i++) {//将文件中保存的地点名称与介绍读取出来
		fscanf(fp2, "%s\n%s", name, intro);
		strcpy(G->nums[i].placename, name);
		strcpy(G->nums[i].intro, intro);
	}

	for (i = 1; i <= G->vexnum; i++) {//初始化顶点关系
		for (j = 1; j <= G->vexnum; j++) {
			G->arcs[i][j] = INF;
		}
	}
	for (j = 1; j <= G->arcnum; j++) {//将文件中个地点之间的关系以及路程读取出来
		fscanf(fp, "%d %d %d", &k, &m, &w);
		G->arcs[k][m] = w;
		G->arcs[m][k] = w;
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp);//关闭文件
}


void Search(AdjGraph G) {
	int flag = 1, choice;
	int flag1 = 0;
	int num = 0, i;
	char* name = (char*)malloc(sizeof(char) * 20);
//	char name[30];
	while (flag == 1) {
		system("cls");
		printf("                           \t┏━━━━━━━━━━━━━━━━━━━━┓\n");
		printf("\t\t\t\t┃  地点信息查询      ┃\n\n");
		printf("\t\t\t\t┃  1:按编号查询      ┃\n\n");
		printf("\t\t\t\t┃  2:按名称查询      ┃\n\n");
		printf("                           \t┗━━━━━━━━━━━━━━━━━━━━┛\n");
		scanf("%d", &choice);
		if (choice == 1) {
			Display_Place(&G);
			printf("\t\t请输入你要查找的地点编号：\n");
			scanf("%d", &num);
			if (num > 0 && num <= G.vexnum) {
				system("cls");
				printf("\n\n您要查找的地点信息如下：\n");
				printf("                           \t┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
				printf("\t\t\t\t┃  编号:%d                        \n\n", num);
				printf("\t\t\t\t┃  名称:%s    \n\n", G.nums[num].placename);
				printf("\t\t\t\t┃  介绍:%s         \n\n", G.nums[num].intro);
				printf("                           \t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
			}
			else {
				printf("\t\t\t\t\t\t信息输入有误!\n");
			}
			printf("\n\n\t\t\t\t如要继续查询请按1，否则请按0退出!");
			scanf("%d", &flag);
		}
		else if (choice == 2) {
			Display_Place(&G);
			printf("\t\t\t\t\t\t请输入需要查询的地点名称：");
			scanf("%s", name);

			for (i = 1; i <= G.vexnum; i++) {

				if (strcmp(G.nums[i].placename, name) == 0) {
					system("cls");
					printf("\n\n您要查找的地点信息如下：\n");
					printf("                           \t┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
					printf("\t\t\t\t┃  编号:%d                        \n\n", i);
					printf("\t\t\t\t┃  名称:%s    \n\n", G.nums[i].placename);
					printf("\t\t\t\t┃  介绍:%s         \n\n", G.nums[i].intro);
					printf("                           \t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
					flag1 = 1;
					break;
				}
			}if (flag1 == 0) {
				printf("\t\t\t\t\t\t\t输入有误!\n");
			}
			printf("\n\n\t\t\t\t如要继续查询请按1，否则请按0退出!");
			scanf("%d", &flag);
		}
		else {
			printf("输入有误,请重新输入!");
			scanf("%d", &flag);
		}
	}
}


void Search_Load(AdjGraph G) {
	int x, flag = 1;
	while (flag == 1) {
		system("cls");
		printf("                           \t┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
		printf("\t\t\t\t┃  1:查询图中任意两个景点间的所有路径┃\n\n");
		printf("\t\t\t\t┃  2:中转次数最少的最短简单路径      ┃\n\n");
		printf("\t\t\t\t┃  3:查询图中任意两个景点间的最短路径┃\n\n");
		printf("\t\t\t\t┃  0:返回                            ┃\n\n");
		printf("                           \t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
		printf("\t\t\t请输入您的选择:\n");
		scanf("%d", &x);

		switch (x) {
		case 1: system("cls"); Simple_Load(G); break;
		case 2: system("cls"); Tansit_Load(G); break;
		case 3: system("cls"); Shortest_Load(G); break;
		case 0: flag = 0; break;
		default:printf("\t\t\t\t\t\t\t输入有误,请重新输入!\n"); break;
		}
		system("cls");
	}
}


void path(AdjGraph* G, int i, int j, int k)
/*确定路径上第k+1个顶点的序号*/
{
	int s;
	if (v[k] == j)/*找到一条路径*/
	{
		a++;/*路径的条数值加1*/
		printf("第%d条:", a);
		for (s = 1; s < k; s++)/*输出一条路径*/
			printf("%s->", G->nums[v[s]].placename);
		printf("%s\n", G->nums[v[s]].placename);

	}
	s = 1;
	while (s <= G->vexnum)
	{
		if (s != i)/*保证找到的是简单路径*/
		{
			if (G->arcs[v[k]][s] != INF && visited[s] == 0)
				/*当vk与vs之间有边存在且vs未被访问过*/
			{
				visited[s] = 1;/*置访问标志位为1,即已访问的*/
				v[k + 1] = s;/*将顶点s加入到v数组中*/
				path(G, i, j, k + 1);/*递归调用之*/
				visited[s] = 0;/*重置访问标志位为0，即未访问的，以便该顶点能被重新使用*/
			}
		}
		s++;
	}
}
void disppath(AdjGraph* G, int i, int j)
{
	int k;
	v[1] = i;
	for (k = 1; k <= G->vexnum; k++)
		visited[i] = 0;/*初始化各顶点的访问标志位，即都为未访问过的*/
	a = 0;/*初始化路径的条数*/
	path(G, i, j, 1);/*通过调用path函数，找到从vi到vj的所有路径并输出*/
}



void Visited(AdjGraph* G) {
	int i;
	for (i = 0; i <= MAXN; i++) {
		G->nums[i].visited = 0; //全部置0 
	}
}



//所有简单路径菜单 
void Simple_Load(AdjGraph G) {
	int s, e;
	int flag = 1;
	while (flag == 1) {
		system("cls");
		printf("\t\t\t\t\t\t★所有简单路径查询★\n");

		Display_Place(&G);

		printf("\n\t\t\t\t\t输入起点编号:");
		scanf("%d", &s);
		printf("\t\t\t\t\t输入终点编号:");
		scanf("%d", &e);

		if (s > G.vexnum || s <= 0 || e > G.vexnum || e < 0 || s == e) {
			printf("\t\t\t\t\t\t输入有误!\n\n");
		}
		else {
			printf("\n\t\t\t\t从%s到%s的所有简单路径有:\n", G.nums[s].placename, G.nums[e].placename);
			disppath(&G, s, e);
		}
		printf("\n\n\t\t\t\t如要继续查询请按1，否则请按0退出!");
		scanf("%d", &flag);
	}
	system("cls");
}


 
void DFS(AdjGraph* G, int s, int e) {
	int shuai = 0;
	int i, j;
	G->nums[s].visited = 1;
	load[count2] = s;
	for (i = 1; i <= G->vexnum; i++) {
		if (G->arcs[s][i] != INF && G->nums[i].visited == 0 && i != e) {
			count2++;
			load[count2] = i;
			DFS(G, i, e); //递归 
			G->nums[i].visited = 0;
			count2--;
			shuai = 0;
			continue;
		} 


		if (G->arcs[s][i] != INF && G->nums[i].visited == 0 && i == e && shuai == 0) {
			count2++;
			load[count2] = e;
			shuai = 1;

			if (count2 < Min) {    
				Min = count2;    
				for (i = 0; i <= count2; i++) {
					Ways[i] = load[i];    
				}
			}

			count2--;
			return;
		}
	}
}


void Tansit_Load(AdjGraph G) {
	int i, j, s, e;
	int flag = 1;

	while (flag == 1) {
		int i;
		system("cls");
		printf("\t\t\t\t\t\t★中转次数最少路径查询★\n");

		Display_Place(&G);

		printf("\n\t\t\t\t\t输入起点编号:");
		scanf("%d", &s);
		printf("\t\t\t\t\t输入终点编号:");
		scanf("%d", &e);
		if (s > G.vexnum || s <= 0 || e > G.vexnum || e < 0 || s == e)
			printf("\t\t\t\t\t\t输入有误!\n\n");

		else {
			Visited(&G);

			Min = MAXN;

			count2 = 0;

			printf("\n\t\t\t\t从%s到%s的中转最少简单路径是:\n", G.nums[s].placename, G.nums[e].placename);
			DFS(&G, s, e);   

			printf("\t\t\t%5s ", G.nums[Ways[0]].placename);

			for (i = 1; i <= Min; i++) {    
				printf("-->");
				printf("%5s ", G.nums[Ways[i]].placename);
			}
			printf("\n\n\t\t\t\t如要继续查询请按1，否则请按0退出!");
			scanf("%d", &flag);
		}
		system("cls");
	}
}
void ShortestPath_DIJ(AdjGraph* G, int v0)// 迪杰斯特拉算法来计算出起点到终点之间的最短路径,v0为起点
{
	int v, w, i, min, x; //v,w,i,x为循环变量，min为最短长度
	int path[MAXNS];   //存放最短路径
	for (v = 1; v <= G->vexnum; v++)
	{
		path[v] = 0;  //假设从顶点v0到顶点v没有最短路径
		Dist[v] = G->arcs[v0][v];  //将与之相关的权值放入D中存放

		for (w = 1; w <= G->vexnum; w++)
			p[v][w] = 0;  //设置为空路径
		if (Dist[v] < INF)  //存在路径
		{
			p[v][v0] = 1;  //存在标志置为一
			p[v][v] = 1;   //自身到自身
		}
	}
	Dist[v0] = 0;
	path[v0] = 1;  //初始化v0顶点属于S集合
	for (i = 1; i <= G->vexnum; i++)  //开始主循环，每一次求得v0到某个顶点的最短路径，并将其加入到S集合
	{
		min = INF;   //当前所知离顶点v0的最近距离
		for (w = 1; w <= G->vexnum; w++)
			if (!path[w])  //w顶点在v-s中
				if (Dist[w] < min) //w顶点离v0顶点更近
				{
					v = w;
					min = Dist[w];//最短长度给min
				}
		path[v] = 1;  //离v0顶点更近的v加入到s集合
		for (w = 1; w <= G->vexnum; w++)
			if (!path[w] && (min + G->arcs[v][w] < Dist[w]))//更新当前最短路径及其距离
			{
				Dist[w] = min + G->arcs[v][w];  // 不在s集合，并且比以前所找到的路径都短就更新当前路径 
				for (x = 1; x <= G->vexnum; x++)
					p[w][x] = p[v][x];
				p[w][w] = 1;
			}
	}

}//ShortestPath_DIJ  end
void output(AdjGraph* G, int sight1, int sight2)    // 输出函数 
{
	int a, b, c, d, q = 0;
	a = sight2;    /* 将景点二赋值给a */
	if (a != sight1)    /* 如果景点二不和景点一输入重合，则进行... */
	{
		printf("\n\t从%s到%s的最短路径是", G->nums[sight1].placename, G->nums[sight2].placename);/* 输出提示信息 */
		printf("\t(最短距离为 %dm.)\n\n\t", Dist[a]);  /* 输出sight1到sight2的最短路径长度，存放在D[]数组中 */
		printf("\t%s", G->nums[sight1].placename);   /* 输出景点一的名称 */
		d = sight1;      /* 将景点一的编号赋值给d */
		for (c = 1; c <= MAXNS; c++)
		{
		gate:;        /* 标号，可以作为goto语句跳转的位置 */
			p[a][sight1] = 0;
			for (b = 1; b <= MAXNS; b++)
			{
				if (G->arcs[d][b] < INF && p[a][b])  /* 如果景点一和它的一个临界点之间存在路径且最短路径 */
				{
					printf("-->%s", G->nums[b].placename);  /* 输出此节点的名称 */
					p[a][b] = 0;
					d = b;     /* 将b作为出发点进行下一次循环输出，如此反复 */
					goto gate;
				}
			}
		}
	}
}

void Shortest_Load(AdjGraph G) {
	int i, j, s, e;
	int flag = 1;
	while (flag == 1) {
		system("cls");
		printf("\t\t\t\t\t\t★最短路径查询★\n");
		Display_Place(&G);
		printf("\n\t\t\t\t\t输入起点编号:");
		scanf("%d", &s);
		printf("\t\t\t\t\t输入终点编号:");
		scanf("%d", &e);
		if (s > G.vexnum || s <= 0 || e > G.vexnum || e < 0 || s == e) {
			printf("\t\t\t\t\t\t输入有误!\n\n");
		}
		else {
			ShortestPath_DIJ(&G, s);
			output(&G, s, e);
		}
		printf("\n\n\t\t\t\t\t如要继续查询请按1，否则请按0退出!");
		scanf("%d", &flag);
	}
	system("cls");
}


int main() {
	int choice;
	printf("\t\t\t       ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t\t\t西安邮电大学长安校区校园导游系统\n");
	printf("\n");
	printf("\t\t\t\t1:游客登录\t    ");
	printf("2:管理员登录\n\n");
	printf("\t\t\t\t\t     0:退出\n");
	printf("\t\t\t        ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("\t\t\t       ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("\t\t\t\t请输入你的选择：\n");
	while (1) {
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			system("cls");
			Tour();
			break;
		case 2:
			system("cls");
			Admin();
			break;
		case 0:
			exit(0);
			break;
		default:
			printf("输入有误，请重新输入！");
			break;
		}
	}
	return 0;
}
