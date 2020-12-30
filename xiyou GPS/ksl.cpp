#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
//#include<graphics.h>

#define true 1
#define false 0
#define MAXN 30//��ʾ�����������
#define MAXNS 50//����������ֵ
#define INF 65535//��ʾ����ֵ

//������·����ȫ�ֱ���
int a = 0;/*ȫ�ֱ�����������¼ÿ�Զ���֮�������·��������*/
int visited[MAXNS];/*ȫ�����飬������¼�����㱻���ʵ����*/
int v[MAXNS];/*ȫ�����飬�������·���ϵĸ�����*/

//��������ת������ȫ�ֱ���
int count2 = 0;
int load[MAXNS] = { 0 }; //·������ 
int Min = MAXN; //��ת���ٶ�������ֵ 
int Ways[MAXNS] = { 0 };//·������ 


//�����·����ȫ�ֱ���
long int Dist[MAXNS];  // ���������洢���·������ 
int p[MAXNS][MAXNS];  //��㵽�յ��·������

typedef struct user//���������û���Ϣ�Ľṹ�� 
{
	char name[50];//�˺� 
	char code[50];//���� 
}User;

typedef struct {//��������ͼ�Ķ�����Ϣ�Ľṹ��
	char placename[50];
	char intro[255];
	int visited;//���ʱ�־
}Vextype;

typedef struct {//�����ڽӾ���ṹ��
	int arcs[MAXN][MAXN];//�ߺͶ���Ķ�Ӧ��ϵ
	Vextype nums[MAXN];//��������
	int vexnum;//������Ŀ
	int arcnum;//�ߵ���Ŀ
}AdjGraph;

void Register();//�û�ע��
void login(AdjGraph G);//�û���¼
int bijiao(User signin);
void Tour();//�ο͵�¼
void Admin();//����Ա��¼
void Admin_Meau(AdjGraph G);//����Ա�˵�

void Append_Data(AdjGraph* G);//�����Ϣ
void Delete_Data(AdjGraph* G);//ɾ����Ϣ
//void Map_Out1();//У԰ʵ��ͼչʾ
void Print_Map();//��ӡ���ֻ�ƽ��ͼ
void Display_Place(AdjGraph* G);//�ص�����������ʾ


void Map_toFile();//����ͼд���ļ�
void Info_Place_tofile();//���ص�����������д���ļ�
void Adj_tofile();//���ڽӾ�����Ϣд���ļ�


void Creat_Graph(AdjGraph* G);//����ͼ
void Search(AdjGraph G);//�ص���Ϣ��ѯ
void Search_Load(AdjGraph G);//��·��ѯ

void path(AdjGraph* G, int i, int j, int k);//����·��
void Visited(AdjGraph* G);

void Simple_Load(AdjGraph G);//���м�·��
void DFS(AdjGraph* G, int s, int e);//��ת����
void Tansit_Load(AdjGraph G);//��ת����
void Shortest_Load(AdjGraph G);//���·��
void ShortestPath_DIJ(AdjGraph* G, int v0);
void output(AdjGraph* G, int sight1, int sight2);

//ע����Ϣ
void Register()
{
	User signin;
	FILE* fp1;
	fp1 = fopen("user.txt", "a+");//�á�a+����ʽ���ļ�������������ļ���д��Ϣ 
	if (fp1 == NULL)
	{
		printf("\t��ʧ��,��������˳���\n");
		exit(1);
	}
	printf("\t�������û�����\n");
	getchar();
	//fgets(signin.name);
	scanf("%s", signin.name);
	printf("\n");
	if (bijiao(signin) == 0)
	{
		printf("\t�Բ�����ע����û����ظ�������������\n");
		getch();
		system("cls");
		Admin();
	}
	else if (bijiao(signin) == 1)
	{
		printf("\t���������룺\n");
		//gets(signin.code);
		scanf("%s", signin.code);
		fputs(signin.name, fp1);
		fputs(" ", fp1);
		fputs(signin.code, fp1);
		fputs("\n", fp1);
		fclose(fp1);
		printf("\t\t*****  ע��ɹ��������������  *****\n");
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
	fp1 = fopen("user.txt", "rt");//�á�rt����ʽ���ļ���ֻ�����ȡ����
	printf("\t�������û�����");
	getchar();
	//gets(ch);
	scanf("%s", ch);
	printf("\t���������룺");
	char a[20];
	int i = 0;
	while ((p[i] = getch()) != '\r')
	{
		if (p[i] == '\b')//��backspace���Ĵ��� 
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
		printf("��¼�ɹ���\n");
		Admin_Meau(G);
	}
	else if (flag == 0)
	{
		printf("\t�������\n");
		getch();
		system("cls");
		Admin();
	}
	else if (flag == 2)
	{
		printf("\t�������û��������ڣ�\n");
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
	fp1 = fopen("user.txt", "rt");//�á�rt����ʽ���ļ���ֻ�����ȡ����
	if (fp1 == NULL)
	{
		printf("\t������Ч�������������ע�ᣡ\n");
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
		printf("                           \t��������������������������������������������\n");
		printf("\t\t\t\t��  1:�ֻ�У԰ƽ��ͼ  ��\n\n");
		printf("\t\t\t\t��  2:У԰ʵ��ͼ      ��\n\n");
		printf("\t\t\t\t��  3:�ص���Ϣ��ѯ    ��\n\n");
		printf("\t\t\t\t��  4:��·��ѯ        ��\n\n");
		printf("\t\t\t\t��  0:�˳�            ��\n\n");
		printf("                           \t��������������������������������������������\n");
		printf("\t\t\t\t����������ѡ��:\n");
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
			printf("�����������������룡\n");
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
	printf("\t\t\t\t1:��¼\t\t");
	printf("2:ע��\n\n");
	printf("\t\t\t\t���������ѡ��");
	while (1) {
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			login(G); break;
		case 2:
			Register(); break;
		default:
			printf("�����������������룡\n");
			break;
		}
	}
}

void Admin_Meau(AdjGraph G) {
	int choice;
	while (1) {

		printf("                           \t����������������������������������������������������\n");
		printf("\t\t\t\t��  1:�ֻ�У԰ƽ��ͼ      ��\n\n");
		printf("\t\t\t\t��  2:У԰ʵ��ͼ          ��\n\n");
		printf("\t\t\t\t��  3:�ص���Ϣ��ѯ        ��\n\n");
		printf("\t\t\t\t��  4:��·��ѯ            ��\n\n");
		printf("\t\t\t\t��  5:������Ϣ            ��\n\n");
		printf("\t\t\t\t��  6:ɾ����Ϣ(��ɾ��·��)��\n\n");
		printf("\t\t\t\t��  0:�˳�                ��\n\n");
		printf("                           \t����������������������������������������������������\n");
		printf("\t\t\t\t����������ѡ��:\n");
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
			printf("�����������������룡\n"); break;
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
		printf("\t\t\t\t������Ҫ��ӵĵص�����:\n");
		scanf("%s",name1);
		getchar();
		printf("\t\t\t\t������Ҫ��ӵĵص����:\n");
		scanf("%s",info1);
		G->vexnum += 1;

		strcpy(G->nums[G->vexnum].placename, name1);
		strcpy(G->nums[G->vexnum].intro, info1);

		FILE* fp;
		fp = fopen(name, "at");
		if (fp == NULL) {
			printf("��ʧ��!\n");
		}

		fprintf(fp, "%s\n%s", G->nums[G->vexnum].placename, G->nums[G->vexnum].intro);
		fclose(fp);

		FILE* fp1;
		fp1 = fopen(data, "wt");
		if (fp1 == NULL) {
			printf("��ʧ��!\n");
		}
		fprintf(fp1, "%d\n%d", G->vexnum, G->arcnum);
		fclose(fp1);

		printf("\t\t\t\t��ӳɹ�!\n");
		printf("\t\t\t\t�Ƿ�ҪΪ�˵ص������·��:\n");
		printf("\t\t\t\t1:��    0:��\n");
		scanf("%d", &flag1);
		
		if (flag1 == 1) {
			Display_Place(G);
			printf("\t\t\t\t�����뵽��ص���:\n");
			scanf("%d", &e);
			printf("\t\t\t\t�����������ص�֮���·��:\n");
			scanf("%d", &w);
			G->arcs[G->vexnum][e] = G->arcs[e][G->vexnum] = w;
			FILE* fp3;
			fp3 = fopen(adj, "at");
			if (fp3 == NULL) {
				printf("��ʧ��!\n");
			}
			fprintf(fp3, "%d %d %d", G->vexnum, e, G->arcs[G->vexnum][e]);
			fclose(fp3);
			G->arcnum += 1;
			fp1 = fopen(data, "wt");
			if (fp1 == NULL) {
				printf("��ʧ��!\n");
			}
			fprintf(fp1, "%d %d\n", G->vexnum, G->arcnum);
			fclose(fp1);

			printf("������!\n");
			flag1 = 0;
		}
		printf("\t\t\t\t����Ҫ��ӵĵص���?\n");
		printf("\t\t\t\t1:��    0:��\n");
		scanf("%d", &flag);
	}
}
void Delete_Data(AdjGraph* G) {
	char data[20] = "data.txt";
	char adj[30] = "adj.txt";
	int flag = 1,s,e;
	while (flag == 1) {
		Display_Place(G);
		printf("������Ҫɾ��·�ߵ����:\n");
		scanf("%d", &s);

		printf("������Ҫɾ��·�ߵ��յ�:\n");
		scanf("%d", &e);

		G->arcs[s][e] = G->arcs[e][s] = INF;

		FILE* fp3;
		fp3 = fopen(adj, "at");
		if (fp3 == NULL) {
			printf("��ʧ��!\n");
		}
		fprintf(fp3, "%d %d %d", s, e, G->arcs[s][e]);
		fclose(fp3);

		G->arcnum -= 1;
		FILE* fp1;
		fp1 = fopen(data, "wt");
		if (fp1 == NULL) {
			printf("��ʧ��!\n");
		}

		fprintf(fp1, "%d\n%d", G->vexnum, G->arcnum);
		fclose(fp1);
		printf("\t\t\t\tɾ���ɹ�!\n");
		printf("\t\t\t\t����Ҫɾ����·����?\n");
		printf("\t\t\t\t1:��    0:��\n");
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
	printf("|                                �������ʵ��ѧ����У԰��ͼ ��                                           |\n");
	printf("|--------------------------------------------------------------------------------------------------------|\n");
	printf("|                                 ����                                                                   |\n");
	printf("|                                 |                                                                      |\n");
	printf("|                                 |                           ��������=======120=======�ݷ�¥            |\n");
	printf("|                                150                                                    |                |\n");
	printf("|                                 |                                                     |                |\n");
	printf("|                                 |                                                    130               |\n");
	printf("|                                 |                                                     |                |\n");
	printf("|                 |=====230====ˮ�����                                                 |                |\n");
	printf("|                 |               |                                                  ������Ԣ            |\n");
	printf("|                 |               |                                                     |                |\n");
	printf("|            ������ѧ¥           |                                                     240              |\n");
	printf("|                 |               |                                                     |                |\n");
	printf("|                 |               |                                                     |                |\n");
	printf("|                 |               |                                                     |                |\n");
	printf("|                200             450                                                    |                |\n");
	printf("|                 |               |                                                   ����Է             |\n");
	printf("|                 |               |                                                     |                |\n");
	printf("|                 |               |                                                     |                |\n");
	printf("|                 |             ͼ���                                                 500               |\n");
	printf("|                 |               |                                                     |                |\n");
	printf("|                 |               |                                                     |                |\n");
	printf("|                 |               |=====================================================|                |\n");
	printf("|                 |              400               |||   ������   |||                   |                |\n");
	printf("|  ҽ����=========|               |=====================================================|                |\n");
	printf("|                                 |                                                                      |\n");
	printf("|                               ������                                                                   |\n");
	printf("|                                 |                                                                      |\n");
	printf("|                                330                                                                     |\n");
	printf("|                                 |                                                                      |\n");
	printf("|                              ����Է                                                                    |\n");
	printf("|                                 |                                                                      |\n");
	printf("|                                210                                                                     |\n");
	printf("|                                 |                                                                      |\n");
	printf("|                             ������Ԣ                                                                   |\n");
	printf("|--------------------------------------------------------------------------------------------------------|\n");
}


void Display_Place(AdjGraph* G) {
	int i;
	system("cls");
	printf("\t\t\t\t\t\t        �������ʵ��ѧ��\n");
	printf("\t\t\t\t\t\t__________________________________\n");
	printf("\t\t\t\t\t\t���\t\t\t����\n");
	for (i = 1; i <= G->vexnum; i++) {
		printf("\t\t\t\t\t\t<%d>\t\t\t%s\n", i, G->nums[i].placename);
	}
}

void Map_toFile() {
	char map[20] = "map.txt";
	FILE* fp;
	fp = fopen(map, "wt");
	if (fp == NULL) {
		printf("���ļ�ʧ�ܣ�");
		return;
	}
	fprintf(fp, "|--------------------------------------------------------------------------------------------------------|\n");
	fprintf(fp, "|                                �������ʵ��ѧ����У԰��ͼ ��                                           |\n");
	fprintf(fp, "|--------------------------------------------------------------------------------------------------------|\n");
	fprintf(fp, "|                                 ����                                                                   |\n");
	fprintf(fp, "|                                 |                                                                      |\n");
	fprintf(fp, "|                                 |                           ��������=======120=======�ݷ�¥            |\n");
	fprintf(fp, "|                                150                                                    |                |\n");
	fprintf(fp, "|                                 |                                                     |                |\n");
	fprintf(fp, "|                                 |                                                    130               |\n");
	fprintf(fp, "|                                 |                                                     |                |\n");
	fprintf(fp, "|                 |=====230====ˮ�����                                                 |                |\n");
	fprintf(fp, "|                 |               |                                                  ������Ԣ            |\n");
	fprintf(fp, "|                 |               |                                                     |                |\n");
	fprintf(fp, "|            ������ѧ¥           |                                                     240              |\n");
	fprintf(fp, "|                 |               |                                                     |                |\n");
	fprintf(fp, "|                 |               |                                                     |                |\n");
	fprintf(fp, "|                 |               |                                                     |                |\n");
	fprintf(fp, "|                200             450                                                    |                |\n");
	fprintf(fp, "|                 |               |                                                   ����Է             |\n");
	fprintf(fp, "|                 |               |                                                     |                |\n");
	fprintf(fp, "|                 |               |                                                     |                |\n");
	fprintf(fp, "|                 |             ͼ���                                                 500               |\n");
	fprintf(fp, "|                 |               |                                                     |                |\n");
	fprintf(fp, "|                 |               |                                                     |                |\n");
	fprintf(fp, "|                 |               |=====================================================|                |\n");
	fprintf(fp, "|                 |              400               |||   ������   |||                   |                |\n");
	fprintf(fp, "|  ҽ����=========|               |=====================================================|                |\n");
	fprintf(fp, "|                                 |                                                                      |\n");
	fprintf(fp, "|                               ������                                                                   |\n");
	fprintf(fp, "|                                 |                                                                      |\n");
	fprintf(fp, "|                                330                                                                     |\n");
	fprintf(fp, "|                                 |                                                                      |\n");
	fprintf(fp, "|                              ����Է                                                                    |\n");
	fprintf(fp, "|                                 |                                                                      |\n");
	fprintf(fp, "|                                210                                                                     |\n");
	fprintf(fp, "|                                 |                                                                      |\n");
	fprintf(fp, "|                             ������Ԣ          	                                                      |\n");
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
		printf("��ʧ��!");
	}

	G.vexnum = 13;

	strcpy(G.nums[1].placename, "ҽ����");
	strcpy(G.nums[1].intro, "λ�������ʵ��ѧ������");
	strcpy(G.nums[2].placename, "������ѧ¥");
	strcpy(G.nums[2].intro, "�����ʵ��ѧ����ѧ���ϿΣ�ѧϰ�ĵط�����ΪA¥��B¥");
	strcpy(G.nums[3].placename, "ˮ�����");
	strcpy(G.nums[3].intro, "�����ʵ��ѧ��Ȫ��λ����������");
	strcpy(G.nums[4].placename, "����");
	strcpy(G.nums[4].intro, "�����ʵ��ѧ����");
	strcpy(G.nums[5].placename, "ͼ���");
	strcpy(G.nums[5].intro, "�����ʵ��ѧͼ��ݣ�����ḻ�����Թ�ѧ������");
	strcpy(G.nums[6].placename, "������");
	strcpy(G.nums[6].intro, "��ͨ�����ʵ��ѧ������������һ��ͨ·");
	strcpy(G.nums[7].placename, "������");
	strcpy(G.nums[7].intro, "�����ʵ��ѧ�����ݣ������ڵ�Ҳ������ģ��ɹ�ѧ�����˶����Ͽ�");
	strcpy(G.nums[8].placename, "����Է");
	strcpy(G.nums[8].intro, "�����ʵ��ѧ����ʳ��");
	strcpy(G.nums[9].placename, "������Ԣ");
	strcpy(G.nums[9].intro, "�����ʵ��ѧ����ѧ����Ϣ��˯���ĵط���λ�������ʵ��ѧ���ϱ�");
	strcpy(G.nums[10].placename, "����Է");
	strcpy(G.nums[10].intro, "�����ʵ��ѧ����ʳ��");
	strcpy(G.nums[11].placename, "������Ԣ");
	strcpy(G.nums[11].intro, "�����ʵ��ѧ����ѧ����Ϣ��˯���ĵط���λ�������ʵ��ѧ���");
	strcpy(G.nums[12].placename, "�ݷ�¥");
	strcpy(G.nums[12].intro, "�����ʵ��ѧ����ѧ���ϿΣ�ѧϰ�ĵط�����A,B,C,D�ĸ����");
	strcpy(G.nums[13].placename, "��������");
	strcpy(G.nums[13].intro, "�����ʵ��ѧ��������");

	//����Ϣ�浽�ļ���
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
		printf("��ʧ��!\n");
		exit(-1);
	}

	FILE* fp1;
	fp1 = fopen(Adj, "wt");
	if (fp1 == NULL) {
		printf("��ʧ��!\n");
		exit(-1);
	}

	G.vexnum = 13;
	G.arcnum = 21;

	fprintf(fp, "%d %d\n", G.vexnum, G.arcnum);//�����������д���ļ�

	for (i = 0; i <= G.vexnum; i++) {//��ʼ��������Ϣ
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



	for (i = 1; i <= G.vexnum; i++) {//���ص�֮��Ĺ�ϵ�Լ�·��д���ļ�
		for (j = 1; j <= G.vexnum; j++) {
			if (G.arcs[i][j] != INF && i < j)
				fprintf(fp1, "%d %d %d\n", i, j, G.arcs[i][j]);
		}
	}

	fclose(fp1);//�ر��ļ�
	fclose(fp);
}


void Creat_Graph(AdjGraph* G) {
	int i, j, k, m, w;
	int vexnum1, arcnum1;
	//char* name = (char*)malloc(sizeof(char) * 20);//�����ݴ��ļ��еĶ�ȡ���ĵص�����
	//char* intro = (char*)malloc(sizeof(char) * 70);//�����ݴ��ļ��ж�ȡ���ĵص����
	char name[20];
	char intro[70];
	FILE* fp1;
	fp1 = fopen("data.txt", "rt");
	if (fp1 == NULL) {
		printf("��ʧ��!");
		exit(-1);
	}

	FILE* fp2;
	fp2 = fopen("info.txt", "rt");
	if (fp2 == NULL) {
		printf("��ʧ��!");
		exit(-1);
	}

	FILE* fp;
	fp = fopen("Adj.txt", "rt");
	if (fp == NULL) {
		printf("��ʧ��!");
		exit(-1);
	}

	fscanf(fp1, "%d %d", &vexnum1, &arcnum1);
	G->vexnum = vexnum1;//������
	G->arcnum = arcnum1;//����

	for (i = 1; i <= G->vexnum; i++) {//���ļ��б���ĵص���������ܶ�ȡ����
		fscanf(fp2, "%s\n%s", name, intro);
		strcpy(G->nums[i].placename, name);
		strcpy(G->nums[i].intro, intro);
	}

	for (i = 1; i <= G->vexnum; i++) {//��ʼ�������ϵ
		for (j = 1; j <= G->vexnum; j++) {
			G->arcs[i][j] = INF;
		}
	}
	for (j = 1; j <= G->arcnum; j++) {//���ļ��и��ص�֮��Ĺ�ϵ�Լ�·�̶�ȡ����
		fscanf(fp, "%d %d %d", &k, &m, &w);
		G->arcs[k][m] = w;
		G->arcs[m][k] = w;
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp);//�ر��ļ�
}


void Search(AdjGraph G) {
	int flag = 1, choice;
	int flag1 = 0;
	int num = 0, i;
	char* name = (char*)malloc(sizeof(char) * 20);
//	char name[30];
	while (flag == 1) {
		system("cls");
		printf("                           \t��������������������������������������������\n");
		printf("\t\t\t\t��  �ص���Ϣ��ѯ      ��\n\n");
		printf("\t\t\t\t��  1:����Ų�ѯ      ��\n\n");
		printf("\t\t\t\t��  2:�����Ʋ�ѯ      ��\n\n");
		printf("                           \t��������������������������������������������\n");
		scanf("%d", &choice);
		if (choice == 1) {
			Display_Place(&G);
			printf("\t\t��������Ҫ���ҵĵص��ţ�\n");
			scanf("%d", &num);
			if (num > 0 && num <= G.vexnum) {
				system("cls");
				printf("\n\n��Ҫ���ҵĵص���Ϣ���£�\n");
				printf("                           \t��������������������������������������������������������������\n");
				printf("\t\t\t\t��  ���:%d                        \n\n", num);
				printf("\t\t\t\t��  ����:%s    \n\n", G.nums[num].placename);
				printf("\t\t\t\t��  ����:%s         \n\n", G.nums[num].intro);
				printf("                           \t��������������������������������������������������������������\n");
			}
			else {
				printf("\t\t\t\t\t\t��Ϣ��������!\n");
			}
			printf("\n\n\t\t\t\t��Ҫ������ѯ�밴1�������밴0�˳�!");
			scanf("%d", &flag);
		}
		else if (choice == 2) {
			Display_Place(&G);
			printf("\t\t\t\t\t\t��������Ҫ��ѯ�ĵص����ƣ�");
			scanf("%s", name);

			for (i = 1; i <= G.vexnum; i++) {

				if (strcmp(G.nums[i].placename, name) == 0) {
					system("cls");
					printf("\n\n��Ҫ���ҵĵص���Ϣ���£�\n");
					printf("                           \t��������������������������������������������������������������\n");
					printf("\t\t\t\t��  ���:%d                        \n\n", i);
					printf("\t\t\t\t��  ����:%s    \n\n", G.nums[i].placename);
					printf("\t\t\t\t��  ����:%s         \n\n", G.nums[i].intro);
					printf("                           \t��������������������������������������������������������������\n");
					flag1 = 1;
					break;
				}
			}if (flag1 == 0) {
				printf("\t\t\t\t\t\t\t��������!\n");
			}
			printf("\n\n\t\t\t\t��Ҫ������ѯ�밴1�������밴0�˳�!");
			scanf("%d", &flag);
		}
		else {
			printf("��������,����������!");
			scanf("%d", &flag);
		}
	}
}


void Search_Load(AdjGraph G) {
	int x, flag = 1;
	while (flag == 1) {
		system("cls");
		printf("                           \t����������������������������������������������������������������������������\n");
		printf("\t\t\t\t��  1:��ѯͼ��������������������·����\n\n");
		printf("\t\t\t\t��  2:��ת�������ٵ���̼�·��      ��\n\n");
		printf("\t\t\t\t��  3:��ѯͼ�������������������·����\n\n");
		printf("\t\t\t\t��  0:����                            ��\n\n");
		printf("                           \t����������������������������������������������������������������������������\n");
		printf("\t\t\t����������ѡ��:\n");
		scanf("%d", &x);

		switch (x) {
		case 1: system("cls"); Simple_Load(G); break;
		case 2: system("cls"); Tansit_Load(G); break;
		case 3: system("cls"); Shortest_Load(G); break;
		case 0: flag = 0; break;
		default:printf("\t\t\t\t\t\t\t��������,����������!\n"); break;
		}
		system("cls");
	}
}


void path(AdjGraph* G, int i, int j, int k)
/*ȷ��·���ϵ�k+1����������*/
{
	int s;
	if (v[k] == j)/*�ҵ�һ��·��*/
	{
		a++;/*·��������ֵ��1*/
		printf("��%d��:", a);
		for (s = 1; s < k; s++)/*���һ��·��*/
			printf("%s->", G->nums[v[s]].placename);
		printf("%s\n", G->nums[v[s]].placename);

	}
	s = 1;
	while (s <= G->vexnum)
	{
		if (s != i)/*��֤�ҵ����Ǽ�·��*/
		{
			if (G->arcs[v[k]][s] != INF && visited[s] == 0)
				/*��vk��vs֮���бߴ�����vsδ�����ʹ�*/
			{
				visited[s] = 1;/*�÷��ʱ�־λΪ1,���ѷ��ʵ�*/
				v[k + 1] = s;/*������s���뵽v������*/
				path(G, i, j, k + 1);/*�ݹ����֮*/
				visited[s] = 0;/*���÷��ʱ�־λΪ0����δ���ʵģ��Ա�ö����ܱ�����ʹ��*/
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
		visited[i] = 0;/*��ʼ��������ķ��ʱ�־λ������Ϊδ���ʹ���*/
	a = 0;/*��ʼ��·��������*/
	path(G, i, j, 1);/*ͨ������path�������ҵ���vi��vj������·�������*/
}



void Visited(AdjGraph* G) {
	int i;
	for (i = 0; i <= MAXN; i++) {
		G->nums[i].visited = 0; //ȫ����0 
	}
}



//���м�·���˵� 
void Simple_Load(AdjGraph G) {
	int s, e;
	int flag = 1;
	while (flag == 1) {
		system("cls");
		printf("\t\t\t\t\t\t�����м�·����ѯ��\n");

		Display_Place(&G);

		printf("\n\t\t\t\t\t���������:");
		scanf("%d", &s);
		printf("\t\t\t\t\t�����յ���:");
		scanf("%d", &e);

		if (s > G.vexnum || s <= 0 || e > G.vexnum || e < 0 || s == e) {
			printf("\t\t\t\t\t\t��������!\n\n");
		}
		else {
			printf("\n\t\t\t\t��%s��%s�����м�·����:\n", G.nums[s].placename, G.nums[e].placename);
			disppath(&G, s, e);
		}
		printf("\n\n\t\t\t\t��Ҫ������ѯ�밴1�������밴0�˳�!");
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
			DFS(G, i, e); //�ݹ� 
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
		printf("\t\t\t\t\t\t����ת��������·����ѯ��\n");

		Display_Place(&G);

		printf("\n\t\t\t\t\t���������:");
		scanf("%d", &s);
		printf("\t\t\t\t\t�����յ���:");
		scanf("%d", &e);
		if (s > G.vexnum || s <= 0 || e > G.vexnum || e < 0 || s == e)
			printf("\t\t\t\t\t\t��������!\n\n");

		else {
			Visited(&G);

			Min = MAXN;

			count2 = 0;

			printf("\n\t\t\t\t��%s��%s����ת���ټ�·����:\n", G.nums[s].placename, G.nums[e].placename);
			DFS(&G, s, e);   

			printf("\t\t\t%5s ", G.nums[Ways[0]].placename);

			for (i = 1; i <= Min; i++) {    
				printf("-->");
				printf("%5s ", G.nums[Ways[i]].placename);
			}
			printf("\n\n\t\t\t\t��Ҫ������ѯ�밴1�������밴0�˳�!");
			scanf("%d", &flag);
		}
		system("cls");
	}
}
void ShortestPath_DIJ(AdjGraph* G, int v0)// �Ͻ�˹�����㷨���������㵽�յ�֮������·��,v0Ϊ���
{
	int v, w, i, min, x; //v,w,i,xΪѭ��������minΪ��̳���
	int path[MAXNS];   //������·��
	for (v = 1; v <= G->vexnum; v++)
	{
		path[v] = 0;  //����Ӷ���v0������vû�����·��
		Dist[v] = G->arcs[v0][v];  //����֮��ص�Ȩֵ����D�д��

		for (w = 1; w <= G->vexnum; w++)
			p[v][w] = 0;  //����Ϊ��·��
		if (Dist[v] < INF)  //����·��
		{
			p[v][v0] = 1;  //���ڱ�־��Ϊһ
			p[v][v] = 1;   //��������
		}
	}
	Dist[v0] = 0;
	path[v0] = 1;  //��ʼ��v0��������S����
	for (i = 1; i <= G->vexnum; i++)  //��ʼ��ѭ����ÿһ�����v0��ĳ����������·������������뵽S����
	{
		min = INF;   //��ǰ��֪�붥��v0���������
		for (w = 1; w <= G->vexnum; w++)
			if (!path[w])  //w������v-s��
				if (Dist[w] < min) //w������v0�������
				{
					v = w;
					min = Dist[w];//��̳��ȸ�min
				}
		path[v] = 1;  //��v0���������v���뵽s����
		for (w = 1; w <= G->vexnum; w++)
			if (!path[w] && (min + G->arcs[v][w] < Dist[w]))//���µ�ǰ���·���������
			{
				Dist[w] = min + G->arcs[v][w];  // ����s���ϣ����ұ���ǰ���ҵ���·�����̾͸��µ�ǰ·�� 
				for (x = 1; x <= G->vexnum; x++)
					p[w][x] = p[v][x];
				p[w][w] = 1;
			}
	}

}//ShortestPath_DIJ  end
void output(AdjGraph* G, int sight1, int sight2)    // ������� 
{
	int a, b, c, d, q = 0;
	a = sight2;    /* ���������ֵ��a */
	if (a != sight1)    /* �����������;���һ�����غϣ������... */
	{
		printf("\n\t��%s��%s�����·����", G->nums[sight1].placename, G->nums[sight2].placename);/* �����ʾ��Ϣ */
		printf("\t(��̾���Ϊ %dm.)\n\n\t", Dist[a]);  /* ���sight1��sight2�����·�����ȣ������D[]������ */
		printf("\t%s", G->nums[sight1].placename);   /* �������һ������ */
		d = sight1;      /* ������һ�ı�Ÿ�ֵ��d */
		for (c = 1; c <= MAXNS; c++)
		{
		gate:;        /* ��ţ�������Ϊgoto�����ת��λ�� */
			p[a][sight1] = 0;
			for (b = 1; b <= MAXNS; b++)
			{
				if (G->arcs[d][b] < INF && p[a][b])  /* �������һ������һ���ٽ��֮�����·�������·�� */
				{
					printf("-->%s", G->nums[b].placename);  /* ����˽ڵ������ */
					p[a][b] = 0;
					d = b;     /* ��b��Ϊ�����������һ��ѭ���������˷��� */
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
		printf("\t\t\t\t\t\t�����·����ѯ��\n");
		Display_Place(&G);
		printf("\n\t\t\t\t\t���������:");
		scanf("%d", &s);
		printf("\t\t\t\t\t�����յ���:");
		scanf("%d", &e);
		if (s > G.vexnum || s <= 0 || e > G.vexnum || e < 0 || s == e) {
			printf("\t\t\t\t\t\t��������!\n\n");
		}
		else {
			ShortestPath_DIJ(&G, s);
			output(&G, s, e);
		}
		printf("\n\n\t\t\t\t\t��Ҫ������ѯ�밴1�������밴0�˳�!");
		scanf("%d", &flag);
	}
	system("cls");
}


int main() {
	int choice;
	printf("\t\t\t       ������������������������������������������������������������������\n");
	printf("\t\t\t\t�����ʵ��ѧ����У��У԰����ϵͳ\n");
	printf("\n");
	printf("\t\t\t\t1:�ο͵�¼\t    ");
	printf("2:����Ա��¼\n\n");
	printf("\t\t\t\t\t     0:�˳�\n");
	printf("\t\t\t        ��������������������������������������������������������������\n");
	printf("\t\t\t       ������������������������������������������������������������������\n");
	printf("\t\t\t\t���������ѡ��\n");
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
			printf("�����������������룡");
			break;
		}
	}
	return 0;
}
