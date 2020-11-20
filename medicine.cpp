#include<stdio.h> //ͷ�ļ� 
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h> 


typedef struct medicine//����һ��ҩƷ�Ľṹ��ָ��
{
	char name[20];//ҩƷ���� 
	char num[20];//ҩƷ��� 
	int price;//ҩƷ���� 
	int amount;//ҩƷ���� 
	struct medicine *next;//��һ����� 
}medicine;


typedef struct user//���������û���Ϣ�Ľṹ�� 
{
	char name[50];//�˺� 
	char code[50];//���� 
}User;


//�������� 
medicine *input_med();//¼�뺯�� 
void output_med(medicine *head);//������� 
medicine *baocun(medicine *head);//����ҩƷ��Ϣ���ļ� 
medicine *read();//���ļ��ж�ȡ��Ϣ 
medicine *print(medicine *head);//��ʾ��Ϣ 
medicine *searchbyname(medicine *head);//�������Ʋ��� 
medicine *searchbybianhao(medicine *head);//���ݱ�Ų��� 
medicine *combination(medicine *head);//��ϲ��� 
medicine *change(medicine *head);//�޸ĺ��� 
medicine *delate(medicine *head);//ɾ������ 
medicine *insert(medicine *head);//���뺯�� 
void tongji(medicine *head); //ͳ�ƺ��� 
medicine *paixu1(medicine *head);//������ 
medicine *paixu2(medicine *head);
medicine *paixu3(medicine *head);
medicine *paixu4(medicine *head);
void paixu(medicine *head);
void search(medicine *head);
void use();//��ҳ 
int bijiao(User signin);//�Ƚ��û�ע���id�Ƿ��ظ� 
void log();//�û�ע�� 
void record();//�û���¼ 


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
	printf("\t\t\t******  1:¼��ҩƷ��Ϣ  *******\n");
	printf("\t\t\t******  2:ɾ��ҩƷ��Ϣ  *******\n");
	printf("\t\t\t******  3:�޸�ҩƷ��Ϣ  *******\n");
	printf("\t\t\t******  4:��ѯҩƷ��Ϣ  *******\n");
	printf("\t\t\t******  5:����ҩƷ��Ϣ  *******\n"); 
	printf("\t\t\t******  6:��ʾҩƷ��Ϣ  *******\n");
	printf("\t\t\t******  7:����ҩƷ��Ϣ  *******\n");
	printf("\t\t\t******  8:������Ϣ���ļ�  *****\n");
	printf("\t\t\t******  9:��д�ļ���Ϣ  *******\n"); 
	printf("\t\t\t******  10:ͳ��ҩƷ��Ϣ  ******\n");
	printf("\t\t\t******  0:����ϵͳ  *************\n"); 
	printf("\t\t���������ѡ��\n");
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
		default :printf("\t������������������,�����������\n");getch();system("cls"); 
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
	printf("\t������Ҫ¼��ҩƷ������\n");
	scanf("%d",&temp);
	if(temp==0)
	{
		printf("\t��������,�����������\n");
		getch();
		home();
	}
	else
	{
	do
	{
	  h=(medicine *)malloc(sizeof(medicine));
	  printf("\t������ҩƷ��Ϣ��\n");
	  printf("\t���ƣ�\n");
	  scanf("%s",h->name);
	  printf("\t��ţ�\n");
	  scanf("%s",h->num);
	  printf("\t�۸�\n");
	  scanf("%d",&h->price);
	  printf("\t������\n");
	  scanf("%d",&h->amount);
	  q->next=h;
	  q=h;
	  h->next=NULL;
	  count++;
    }while(count<temp);
    }
    printf("\t¼����ϣ�\n");
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
		printf("\tĿǰ��δ¼��ҩƷ��Ϣ������������أ�\n");
		getch();	
		system("cls");	
		return ;	
	}
	printf("\tҩƷ��Ϣ������ʾ��\n");
	p=head->next;
	printf("\n\n                              --ҩƷ��Ϣ--                           \n\n");
	printf("\t-------------------------------------------------------------------------\n");
	printf("\t����------------���------------����----------����--------------------\n");
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
	printf("\t\������в������ɴ����ļ��У�\n");
	printf("\t����Ҫ������ļ�����  ");
	scanf("%s",filename);
	if ((fp = fopen(filename, "a+")) == NULL)//�á�a+����ʽ���ļ�������������ļ���д��Ϣ 
	{
		printf("\tд�ļ�������������˳���");
		getch();
		exit(1);
	}
	for(p=head->next;p!=NULL;p=p->next)
	{
		fprintf(fp,"%s %s %d %d",p->name,p->num,p->price,p->amount);
	}
	fclose(fp);
	printf("\t��Ϣ�������\n");
	getch();
	system("cls");
	return head;
	
}
medicine *read()
{
	medicine *head, *q, *p;
	FILE *fp;
	char filename[40];
	printf("\t����Ҫ�򿪵��ļ�����   ");
	scanf("%s", filename);
	if ((fp = fopen(filename, "rt")) == NULL)//�á�rt����ʽ���ļ���ֻ�����ȡ���� 
	{
		printf("\t���ļ��д���������˳���");
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
	printf("\n\t�ļ��Ѷ��������������ʾ��\n");
	fclose(fp);
	getch();
	return head;
}
medicine *print(medicine *head)
{
	system("cls");
	medicine *p=head->next;
	printf("\tҩƷ��Ϣ������ʾ��\n");
	printf("\n\n                              --ҩƷ��Ϣ--                           \n\n");
	printf("\t-------------------------------------------------------------------------\n");
	printf("\t����------------���-------------����-----------����--------------------\n");
	while (p!=NULL)
	{
		printf("\t%-16s%-16s%-15d%-16.1d\n", p->name, p->num, p->price,p->amount);
		p = p->next;
	}	
	printf("\t�����������!\n");
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
	printf("\t������Ҫ��ѯҩƷ�����ƣ�\n");
	scanf("%s",name1);
	while(p!=NULL)
	{
		if(strcmp(p->name,name1)==0)
		{
			printf("\tҩƷ��Ϣ������ʾ��\n");
	        printf("\n\n                              --ҩƷ��Ϣ--                           \n\n");
	        printf("\t-------------------------------------------------------------------------\n");
	        printf("\t����------------���-------------����-----------����--------------------\n");
	        printf("\t%-17s%-16s%-15d%-16.1d\n", p->name, p->num, p->price, p->amount);
			count++;
		}
		p=p->next;
	}
	if(count>1)
	{
		printf("\tҩƷ�������ظ����Ƿ���н�һ���Ĳ�ѯ\n");
	    printf("\t\t*************  1:��  ************\n");
	    printf("\t\t*************  2:��  ************\n");
	    scanf("%d",&choice);
	switch(choice)
	{
		case 1:searchbybianhao(head);break;
		case 2:break;
		default :printf("\t��������\n");break;
	}
    }else if(count==0)
    {
    	printf("\tδ�ҵ���ҩƷ����Ϣ\n");
	}
   
	printf("\t�����������\n");
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
	printf("\t������Ҫ��ѯҩƷ�ı�ţ�\n");
	scanf("%s",num1);
	while(p!=NULL)
	{
		if(strcmp(p->num,num1)==0)
		{
			printf("\tҩƷ��Ϣ������ʾ��\n");
	        printf("\n\n                              --ҩƷ��Ϣ--                           \n\n");
	        printf("\t-------------------------------------------------------------------------\n");
	        printf("\t����------------���-------------����-----------����--------------------\n");
	        printf("\t%-17s%-16s%-15d%-16.1d\n", p->name, p->num, p->price, p->amount);
			count++;
		}
		p=p->next;
	}
	if(count>1)
	{
		printf("\tҩƷ������ظ����Ƿ���н�һ���Ĳ�ѯ\n");
	    printf("\t\t*************  1:��  ************\n");
	    printf("\t\t*************  2:��  ************\n");
	    scanf("%d",&choice);
	switch(choice)
	{
		case 1:searchbyname(head);break;
		case 2:break;
		default :printf("\t��������\n");break;
	}
    }else if(count==0)
    {
    	printf("\tδ�ҵ���ҩƷ����Ϣ\n");
	}
   
	printf("\t�����������\n");
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
	printf("\t������Ҫ��ѯҩƷ�����ƣ�\n");
	scanf("%s",name3);
	printf("\t������Ҫ��ѯҩƷ�ı�ţ�\n");
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
		    printf("\tҩƷ��Ϣ������ʾ��\n");
	        printf("\n\n                              --ҩƷ��Ϣ--                           \n\n");
	        printf("\t-------------------------------------------------------------------------\n");
	        printf("\t����------------���-------------����-----------����--------------------\n");
	        printf("\t%-17s%-16s%-15d%-16.1d\n", h->name, h->num, h->price, h->amount);
	}
	else
	{
		printf("\tδ�ҵ���ҩƷ����Ϣ\n");
	}
	printf("\t�����������\n");
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
	printf("\t������Ҫ�޸ĵ�ҩƷ���ƣ�\n");
	scanf("%s",name4);
	while(q&&strcmp(q->name,name4)!=0)
	{
		q=q->next;
	}
	if(q)
	{
		printf("\t�޸�ǰҩƷ��Ϣ���£�\n") ;
		printf("\n\n                              --ҩƷ��Ϣ--                           \n\n");
	    printf("\t-------------------------------------------------------------------------\n");
	    printf("\t����------------���-------------����-----------����--------------------\n");
		printf("\t%-16s%-16s%-15d%-16.1d\n", q->name, q->num, q->price,q->amount);
		printf("\t�������޸�������ƣ�\n");
		scanf("%s",q->name);
		printf("\t�������޸���ı�ţ�\n");
		scanf("%s",q->num);
		printf("\t�������޸���ĵ��ۣ�\n");
		scanf("%d",&q->price);
		printf("\t�������޸����������\n");
		scanf("%d",&q->amount);
		printf("\t�޸ĳɹ���\n");
		count++;
	}
	if(count==0)
	{
	      printf("\tû�ҵ���ҩƷ����Ϣ������������,�����������\n"); 
	}
	else
	{ 
	printf("\t����������أ�\n");
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
	printf("\t��������Ҫɾ����ҩƷ���ƣ�\n");
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
		printf("\tû�ҵ���ҩƷ����Ϣ������������,�����������\n");
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
	printf("\tɾ����ɣ�\n");
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
	printf("\t������Ҫ����ҩƷ����Ϣ��\n");
	printf("\t���ƣ�\n");
	scanf("%s",q->name);
	printf("\t��ţ�\n");
	scanf("%s",q->num);
	printf("\t���ۣ�\n");
	scanf("%d",&q->price);
	printf("\t������\n");
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
	printf("\t������ɣ���������˳�\n");
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
	printf("\t��¼��ҩƷ�۸��ƽ��ֵΪ��%.2f\n",ave);
	while(q!=NULL)
	{
		if(q->price>ave)
		{
			count1++;
		}
		q=q->next;
	}
	printf("\t����ƽ��ֵ��ҩƷ����Ϊ��%d\n",count1);
	printf("\t�����������\n");
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
	printf("\t\t\t�����������������Ϣ��\n");
	printf("\t\t\t*****  1:ҩƷ����(�Ӹߵ���)  *****\n");
	printf("\t\t\t*****  2:ҩƷ����(�ӵ͵���)  *****\n");
	printf("\t\t\t*****  3:ҩƷ����(�Ӹߵ���)  *****\n");
	printf("\t\t\t*****  4:ҩƷ����(�ӵ͵���)  *****\n");
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
	printf("\t\t\t��ѡ������Ҫ�Ĳ�ѯ��ʽ��\n");
	printf("\t\t\t*****  1:�������Ʋ�ѯ  ********\n");
	printf("\t\t\t*****  2:�����Ų�ѯ  ********\n");
	printf("\t\t\t*****  3:�������ƺͱ�Ų�ѯ  **\n");
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
	printf("\t\t\t*****  ҩ�����ϵͳ  *****\n");
	printf("\t\t\t********  1:��¼  ********\n");
	printf("\t\t\t********  2:ע��  ********\n");
	printf("\t\t\t********  3:�˳�  ********\n");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:record();break;
		case 2:log();break;
		case 3:exit(0);
		default :printf("\tѡ�����������ѡ��\n");getch();use();
	} 
}
void log()
{
	User signin;
	FILE  *fp1;
	fp1 = fopen("user.txt", "a+");//�á�a+����ʽ���ļ�������������ļ���д��Ϣ 
	if (fp1 == NULL)
	{
		printf("\t��ʧ��,��������˳���\n");
		exit(1);
	}
	printf("\t�������û�����\n");
	getchar();
	gets(signin.name);
	printf("\n");
	if (bijiao(signin) == 0)
	{
		printf("\t�Բ�����ע����û����ظ�������������\n");
		getch();
		system("cls");
		use();
	}
	else if (bijiao(signin) == 1)
	{
		printf("\t���������룺\n");
		gets(signin.code);
		fputs(signin.name, fp1);
		fputs(" ", fp1);
		fputs(signin.code, fp1);
		fputs("\n", fp1);
		fclose(fp1);
		printf("\t\t*****  ע��ɹ��������������  *****\n");
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
	fp1 = fopen("user.txt", "rt");//�á�rt����ʽ���ļ���ֻ�����ȡ����
	printf("\t�������û�����");
	getchar();
	gets(ch);
	printf("\t���������룺");
	char a[20];
	int i=0;
    while((p[i]=getch())!='\r')
    {
    if(p[i]=='\b')//��backspace���Ĵ��� 
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
			printf("\t�������\n");
			getch();
			system("cls"); 
			use();
		}
		else if(flag ==2)
		{
			printf("\t�������û��������ڣ�\n");
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







