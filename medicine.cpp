#include<stdio.h> //头文件 
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h> 


typedef struct medicine//创建一个药品的结构体指针
{
	char name[20];//药品名称 
	char num[20];//药品编号 
	int price;//药品单价 
	int amount;//药品数量 
	struct medicine *next;//下一个结点 
}medicine;


typedef struct user//创建关于用户信息的结构体 
{
	char name[50];//账号 
	char code[50];//密码 
}User;


//函数声明 
medicine *input_med();//录入函数 
void output_med(medicine *head);//输出函数 
medicine *baocun(medicine *head);//保存药品信息到文件 
medicine *read();//从文件中读取信息 
medicine *print(medicine *head);//显示信息 
medicine *searchbyname(medicine *head);//根据名称查找 
medicine *searchbybianhao(medicine *head);//根据编号查找 
medicine *combination(medicine *head);//组合查找 
medicine *change(medicine *head);//修改函数 
medicine *delate(medicine *head);//删除函数 
medicine *insert(medicine *head);//插入函数 
void tongji(medicine *head); //统计函数 
medicine *paixu1(medicine *head);//排序函数 
medicine *paixu2(medicine *head);
medicine *paixu3(medicine *head);
medicine *paixu4(medicine *head);
void paixu(medicine *head);
void search(medicine *head);
void use();//主页 
int bijiao(User signin);//比较用户注册的id是否重复 
void log();//用户注册 
void record();//用户登录 


int main()
{
	system("color 06");
	use();
	return 0;
}

void home()
{
	system("cls");
	int select=1; 
	medicine *head=NULL;
	while(select!=0)
	{
	printf("\t\t\t******  1:录入药品信息  *******\n");
	printf("\t\t\t******  2:删除药品信息  *******\n");
	printf("\t\t\t******  3:修改药品信息  *******\n");
	printf("\t\t\t******  4:查询药品信息  *******\n");
	printf("\t\t\t******  5:插入药品信息  *******\n"); 
	printf("\t\t\t******  6:显示药品信息  *******\n");
	printf("\t\t\t******  7:排序药品信息  *******\n");
	printf("\t\t\t******  8:保存信息到文件  *****\n");
	printf("\t\t\t******  9:读写文件信息  *******\n"); 
	printf("\t\t\t******  10:统计药品信息  ******\n");
	printf("\t\t\t******  0:结束系统  *************\n"); 
	printf("\t\t请输入你的选择：\n");
	scanf("%d",&select); 
	fflush(stdin);
	switch(select)
	{
		case 1:head=input_med();break;
		case 2:delate(head);break;
		case 3:change(head);break;
		case 4:search(head);break;
		case 5:insert(head);break;
		case 6:output_med(head);break;
		case 7:paixu(head);break;
		case 8:baocun(head);break;
		case 9:	head=read();head=print(head);break;
		case 10:tongji(head);break;
		case 0:return ; 
		default :printf("\t输入有误，请重新输入,按任意键继续\n");getch();system("cls"); 
		break;
	}
    }	
} 
medicine *input_med()
{
	int count=0,temp;
	medicine *q,*p,*h;
	p=(medicine *)malloc(sizeof(medicine));
	p->next=NULL;
	q=p;
	system("cls");
	printf("\t请输入要录入药品数量：\n");
	scanf("%d",&temp);
	if(temp==0)
	{
		printf("\t输入有误,按任意键继续\n");
		getch();
		home();
	}
	else
	{
	do
	{
	  h=(medicine *)malloc(sizeof(medicine));
	  printf("\t请输入药品信息：\n");
	  printf("\t名称：\n");
	  scanf("%s",h->name);
	  printf("\t编号：\n");
	  scanf("%s",h->num);
	  printf("\t价格：\n");
	  scanf("%d",&h->price);
	  printf("\t数量：\n");
	  scanf("%d",&h->amount);
	  q->next=h;
	  q=h;
	  h->next=NULL;
	  count++;
    }while(count<temp);
    }
    printf("\t录入完毕！\n");
    getch();
    system("cls");
    return p;
}	
void output_med(medicine *head)
{
	system("cls");
	medicine *p=head;
	if(p==NULL)
	{
		printf("\t目前尚未录入药品信息，按任意键返回！\n");
		getch();	
		system("cls");	
		return ;	
	}
	printf("\t药品信息如下所示：\n");
	p=head->next;
	printf("\n\n                              --药品信息--                           \n\n");
	printf("\t-------------------------------------------------------------------------\n");
	printf("\t名称------------编号------------单价----------数量--------------------\n");
	while (p!=NULL)
	{
		printf("\t%-16s%-16s%-15d%-16.1d\n", p->name, p->num, p->price,p->amount);
		p = p->next;
	}
}
medicine *baocun(medicine *head)
{
	FILE *fp;
	medicine *p;
	char filename[20];
	printf("\t\完成所有操作后便可存入文件中！\n");
	printf("\t输入要保存的文件名：  ");
	scanf("%s",filename);
	if ((fp = fopen(filename, "a+")) == NULL)//用‘a+’方式打开文件，方便后续往文件里写信息 
	{
		printf("\t写文件出错，按任意键退出！");
		getch();
		exit(1);
	}
	for(p=head->next;p!=NULL;p=p->next)
	{
		fprintf(fp,"%s %s %d %d",p->name,p->num,p->price,p->amount);
	}
	fclose(fp);
	printf("\t信息保存完成\n");
	getch();
	system("cls");
	return head;
	
}
medicine *read()
{
	medicine *head, *q, *p;
	FILE *fp;
	char filename[40];
	printf("\t输入要打开的文件名：   ");
	scanf("%s", filename);
	if ((fp = fopen(filename, "rt")) == NULL)//用‘rt’方式打开文件，只允许读取数据 
	{
		printf("\t打开文件有错，按任意键退出！");
		getch();
		exit(1);
	}
	head = (medicine *)malloc(sizeof(medicine));
	head->next = NULL;
	q = head;
	while (!feof(fp)) {
		p = (medicine *)malloc(sizeof(medicine));
		fscanf(fp,"%s %s %d %d\n", p->name, p->num, &p->price,&p->amount);
		q->next = p;
		q = p;
	}
	q->next = NULL;
	printf("\n\t文件已读出，按任意键显示！\n");
	fclose(fp);
	getch();
	return head;
}
medicine *print(medicine *head)
{
	system("cls");
	medicine *p=head->next;
	printf("\t药品信息如下所示：\n");
	printf("\n\n                              --药品信息--                           \n\n");
	printf("\t-------------------------------------------------------------------------\n");
	printf("\t名称------------编号-------------单价-----------数量--------------------\n");
	while (p!=NULL)
	{
		printf("\t%-16s%-16s%-15d%-16.1d\n", p->name, p->num, p->price,p->amount);
		p = p->next;
	}	
	printf("\t按任意键返回!\n");
	getch();
	system("cls");
	return head;
} 
medicine *searchbyname(medicine *head)
{
	system("cls");
	int count=0,choice;
	medicine *p;
	p=head;
	char name1[20];
	printf("\t请输入要查询药品的名称：\n");
	scanf("%s",name1);
	while(p!=NULL)
	{
		if(strcmp(p->name,name1)==0)
		{
			printf("\t药品信息如下所示：\n");
	        printf("\n\n                              --药品信息--                           \n\n");
	        printf("\t-------------------------------------------------------------------------\n");
	        printf("\t名称------------编号-------------单价-----------数量--------------------\n");
	        printf("\t%-17s%-16s%-15d%-16.1d\n", p->name, p->num, p->price, p->amount);
			count++;
		}
		p=p->next;
	}
	if(count>1)
	{
		printf("\t药品名称有重复，是否进行进一步的查询\n");
	    printf("\t\t*************  1:是  ************\n");
	    printf("\t\t*************  2:否  ************\n");
	    scanf("%d",&choice);
	switch(choice)
	{
		case 1:searchbybianhao(head);break;
		case 2:break;
		default :printf("\t输入有误\n");break;
	}
    }else if(count==0)
    {
    	printf("\t未找到该药品的信息\n");
	}
   
	printf("\t按任意键返回\n");
	getch();
	system("cls");
	return head;
}
medicine *searchbybianhao(medicine *head)
{
	system("cls");
	int count=0,choice;
	medicine *p;
	p=head;
	char num1[20];
	printf("\t请输入要查询药品的编号：\n");
	scanf("%s",num1);
	while(p!=NULL)
	{
		if(strcmp(p->num,num1)==0)
		{
			printf("\t药品信息如下所示：\n");
	        printf("\n\n                              --药品信息--                           \n\n");
	        printf("\t-------------------------------------------------------------------------\n");
	        printf("\t名称------------编号-------------单价-----------数量--------------------\n");
	        printf("\t%-17s%-16s%-15d%-16.1d\n", p->name, p->num, p->price, p->amount);
			count++;
		}
		p=p->next;
	}
	if(count>1)
	{
		printf("\t药品编号有重复，是否进行进一步的查询\n");
	    printf("\t\t*************  1:是  ************\n");
	    printf("\t\t*************  2:否  ************\n");
	    scanf("%d",&choice);
	switch(choice)
	{
		case 1:searchbyname(head);break;
		case 2:break;
		default :printf("\t输入有误\n");break;
	}
    }else if(count==0)
    {
    	printf("\t未找到该药品的信息\n");
	}
   
	printf("\t按任意键返回\n");
	getch();
	system("cls");
	return head;
	
}
medicine *combination(medicine *head)
{
	system("cls");
	medicine *p,*q,*h;
	int count=0,temp=0;
	p=q=head;
	h=head->next;
	char name3[20];
	char number1[20];
	printf("\t请输入要查询药品的名称：\n");
	scanf("%s",name3);
	printf("\t请输入要查询药品的编号：\n");
	scanf("%s",number1);
	while(p!=NULL)
	{
	  if(strcmp(p->name,name3)==0)
	  {
		  count++;
      }
       p=p->next;
	} 
	while(q!=NULL)
	{
	  if(strcmp(q->num,number1)==0)
	  {
		  temp++;
      }
       q=q->next;
	}
	if(count!=0&&temp!=0)
	{
		    printf("\t药品信息如下所示：\n");
	        printf("\n\n                              --药品信息--                           \n\n");
	        printf("\t-------------------------------------------------------------------------\n");
	        printf("\t名称------------编号-------------单价-----------数量--------------------\n");
	        printf("\t%-17s%-16s%-15d%-16.1d\n", h->name, h->num, h->price, h->amount);
	}
	else
	{
		printf("\t未找到该药品的信息\n");
	}
	printf("\t按任意键返回\n");
	getch();
	system("cls");
	return head;
} 
medicine *change(medicine *head)
{
	system("cls");
	int count=0;
	medicine *q;
	q=head;
	char name4[20];
	printf("\t请输入要修改的药品名称：\n");
	scanf("%s",name4);
	while(q&&strcmp(q->name,name4)!=0)
	{
		q=q->next;
	}
	if(q)
	{
		printf("\t修改前药品信息如下：\n") ;
		printf("\n\n                              --药品信息--                           \n\n");
	    printf("\t-------------------------------------------------------------------------\n");
	    printf("\t名称------------编号-------------单价-----------数量--------------------\n");
		printf("\t%-16s%-16s%-15d%-16.1d\n", q->name, q->num, q->price,q->amount);
		printf("\t请输入修改完的名称：\n");
		scanf("%s",q->name);
		printf("\t请输入修改完的编号：\n");
		scanf("%s",q->num);
		printf("\t请输入修改完的单价：\n");
		scanf("%d",&q->price);
		printf("\t请输入修改完的数量：\n");
		scanf("%d",&q->amount);
		printf("\t修改成功！\n");
		count++;
	}
	if(count==0)
	{
	      printf("\t没找到该药品的信息，请重新输入,按任意键返回\n"); 
	}
	else
	{ 
	printf("\t按任意键返回！\n");
	} 
	getch();
	system("cls");
	return head;
}
medicine *delate(medicine *head)
{
	system("cls");
	medicine *p,*q,*h;
	int count=0;
	h=p=head;
	q=head->next;
	char name5[20];
	printf("\t请输入你要删除的药品名称：\n");
	scanf("%s",name5);
	while(h!=NULL)
	{
		if(strcmp(h->name,name5)==0)
		{
			count++;
		}
		h=h->next;
	}
	if(count==0)
	{
		printf("\t没找到该药品的信息，请重新输入,按任意键返回\n");
	} 
	else
	{
	while(q!=NULL)
	{
		if(strcmp(q->name,name5)==0)
		{
			p->next=q->next;
			free(q);
			q=p->next;
		}
		else
		{
			q=q->next;
			p=p->next;
		}
	}
	printf("\t删除完成！\n");
    }
	getch();
	return head;
}
medicine *insert(medicine *head)
{
	system("cls");
	medicine *p,*q;
	q=(medicine *)malloc(sizeof(medicine));
	p=head;
	printf("\t请输入要插入药品的信息：\n");
	printf("\t名称：\n");
	scanf("%s",q->name);
	printf("\t编号：\n");
	scanf("%s",q->num);
	printf("\t单价：\n");
	scanf("%d",&q->price);
	printf("\t数量：\n");
	scanf("%d",&q->amount);
	while(p->next!=NULL&&p->next->num<q->num)
	p=p->next;
	if(p->next!=NULL&&p->next->num==p->num)
	{
		free(q);
		return 0;
	}
	q->next=p->next;
	p->next=q;
	printf("\t插入完成，按任意键退出\n");
	getch();
	system("cls");
	return p;
}
void tongji(medicine *head)
{
	system("cls");
	medicine *p,*q;
	int sum,temp=0,count1=0;
	float ave;
	q=p=head->next;
	while(p!=NULL)
	{
		sum+=p->price;
		temp++;
		p=p->next;
	}
	ave=(sum*1.0)/temp;
	printf("\t已录入药品价格的平均值为：%.2f\n",ave);
	while(q!=NULL)
	{
		if(q->price>ave)
		{
			count1++;
		}
		q=q->next;
	}
	printf("\t超过平均值的药品数量为：%d\n",count1);
	printf("\t按任意键继续\n");
	getch();
	system("cls");
}
medicine *paixu1(medicine *head)
{
	medicine *p, *q, *h;
	h=NULL;
	while (h != head->next)
	{
		p=head;
		q=p->next;
		while (q->next != h)
		{
			if (p->next->price<q->next->price)
			{
				p->next = q->next;
				q->next = q->next->next;
				p->next->next = q;
			}
			p = p->next;
			q = p->next;
		}
		h = q;
	}
	return(head);
}
medicine *paixu2(medicine *head)
{
	medicine *p, *q, *h;
	h=NULL;
	while (h != head->next)
	{
		p=head;
		q=p->next;
		while (q->next != h)
		{
			if (p->next->price>q->next->price)
			{
				p->next = q->next;
				q->next = q->next->next;
				p->next->next = q;
			}
			p = p->next;
			q = p->next;
		}
		h = q;
	}
	return(head);
}
medicine *paixu3(medicine *head)
{
	medicine *p, *q, *h;
	h=NULL;
	while (h != head->next)
	{
		p=head;
		q=p->next;
		while (q->next != h)
		{
			if (p->next->amount<q->next->amount)
			{
				p->next = q->next;
				q->next = q->next->next;
				p->next->next = q;
			}
			p = p->next;
			q = p->next;
		}
		h = q;
	}
	return(head);
}
medicine *paixu4(medicine *head)
{
	medicine *p, *q, *h;
	h=NULL;
	while (h != head->next)
	{
		p=head;
		q=p->next;
		while (q->next != h)
		{
			if (p->next->amount>q->next->amount)
			{
				p->next = q->next;
				q->next = q->next->next;
				p->next->next = q;
			}
			p = p->next;
			q = p->next;
		}
		h = q;
	}
	return(head);
}
void paixu(medicine *head)
{
	int choice;
	printf("\t\t\t请输入你想排序的信息：\n");
	printf("\t\t\t*****  1:药品单价(从高到低)  *****\n");
	printf("\t\t\t*****  2:药品单价(从低到高)  *****\n");
	printf("\t\t\t*****  3:药品数量(从高到低)  *****\n");
	printf("\t\t\t*****  4:药品数量(从低到高)  *****\n");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:paixu1(head);print(head);break;
		case 2:paixu2(head);print(head);break;
		case 3:paixu3(head);print(head);break;
		case 4:paixu4(head);print(head);break;
	}
}
void search(medicine *head)
{
	int choice;
	printf("\t\t\t请选择你需要的查询方式：\n");
	printf("\t\t\t*****  1:输入名称查询  ********\n");
	printf("\t\t\t*****  2:输入编号查询  ********\n");
	printf("\t\t\t*****  3:输入名称和编号查询  **\n");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:searchbyname(head);break;
		case 2:searchbybianhao(head);break;
		case 3:combination(head);break;
	}
}
void use()
{
	int choice;
	printf("\t\t\t*****  药店管理系统  *****\n");
	printf("\t\t\t********  1:登录  ********\n");
	printf("\t\t\t********  2:注册  ********\n");
	printf("\t\t\t********  3:退出  ********\n");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:record();break;
		case 2:log();break;
		case 3:exit(0);
		default :printf("\t选择错误，请重新选择\n");getch();use();
	} 
}
void log()
{
	User signin;
	FILE  *fp1;
	fp1 = fopen("user.txt", "a+");//用‘a+’方式打开文件，方便后续往文件里写信息 
	if (fp1 == NULL)
	{
		printf("\t打开失败,按任意键退出！\n");
		exit(1);
	}
	printf("\t请输入用户名：\n");
	getchar();
	gets(signin.name);
	printf("\n");
	if (bijiao(signin) == 0)
	{
		printf("\t对不起，您注册的用户名重复，请重新输入\n");
		getch();
		system("cls");
		use();
	}
	else if (bijiao(signin) == 1)
	{
		printf("\t请设置密码：\n");
		gets(signin.code);
		fputs(signin.name, fp1);
		fputs(" ", fp1);
		fputs(signin.code, fp1);
		fputs("\n", fp1);
		fclose(fp1);
		printf("\t\t*****  注册成功，按任意键返回  *****\n");
		getch();
		system("cls");
		use();
	}
}
void record()
{
	User log;
	FILE *fp1;
	int flag=0;
	char ch[50],p[50];
	fp1 = fopen("user.txt", "rt");//用‘rt’方式打开文件，只允许读取数据
	printf("\t请输入用户名：");
	getchar();
	gets(ch);
	printf("\t请输入密码：");
	char a[20];
	int i=0;
    while((p[i]=getch())!='\r')
    {
    if(p[i]=='\b')//对backspace键的处理 
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
    p[i]='\0';
	while(fscanf(fp1,"%s %s",log.name,log.code)!=EOF)
	{	
		if( strcmp(ch,log.name)==0&&strcmp(p,log.code)==0 )
		{	
				flag=1;
				break;	
        }
			else if(strcmp(ch,log.name)==0&&strcmp(p,log.code)!=0)
			{	
				flag=0;
				break;
			}
		else if(strcmp(ch,log.name)!=0)
		{
             flag=2;	
			continue;
		}
	}
		if(flag==1)
		{
			printf("\n");
			home();
		}
		else if(flag ==0)
		{
			printf("\t密码出错！\n");
			getch();
			system("cls"); 
			use();
		}
		else if(flag ==2)
		{
			printf("\t您输入用户名不存在！\n");
			getch();
			system("cls"); 
			use();
		}
	
}
int bijiao(User signin)
{
	FILE *fp1;
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







