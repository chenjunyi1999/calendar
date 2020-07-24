#include<stdlib.h>
#include<string.h>
#include<stdio.h>
struct holiday
{
	int m;
	int d;
	char name[30];
    int whatweek;
	int week;
};
struct Date{                          //�������ڽṹ��
	int day;
	int month;
	int year;
	int week;                         //Ϊ�˷���week��������µ�һ�����ܼ�
}date;
char mon[12][12];                      //����һ������ �洢�·�
void inputdate()                       //��������
{
	
	printf("����������\n");
	scanf("%d.%d.%d",&date.year,&date.month,&date.day);
}
void week()                           //��������
{
    int week,y,c,m,d;
	c=date.year/100;
	y=date.year-c*100;
	m=date.month;
	d=1;
	if(date.month<3)
	{
		int year;
		m=date.month+12;
		year=date.year-1;
		c=date.year/100;
	    y=year-c*100;
	}
	week=(y+y/4+c/4-2*c+26*(m+1)/10+d-1)%7;
	date.week=week;
	if(date.week<0)
		date.week+=7;
	
}
int judge(FILE *fp,FILE *p,int i)                            //�ж��Ƿ��ǽ���
{
	struct holiday h;
	struct holiday h2;
	fp=fopen("D:\\file.txt","a+");
	p=fopen("D:\\file2.txt","a+");
	if(fp==0||p==0)
	{
		printf("file error\n");
		exit(1);
	}
	int f=0;
	fscanf(fp,"%d%d%s",&h.m,&h.d,h.name);
	fscanf(p,"%d%d%d%s",&h2.m,&h2.whatweek,&h2.week,h2.name);
	while(!feof(fp))
	{
		if(date.month==h.m)
		{
			if(i==h.d)
			{
				f=1;
			}
		}
		fscanf(fp,"%d%d%s",&h.m,&h.d,h.name);
	}
	while(!feof(p))
	{	
		if(date.month==h2.m)
		{ 
			if(i==((h2.whatweek-1)*7+h2.week-date.week+1))
				{
					f=1;
					break;
				}
		}
		fscanf(p,"%d%d%d%s",&h2.m,&h2.whatweek,&h2.week,h2.name);
	}
	fclose(fp);
	fclose(p);
    return f;
}

void print(int day)                             //�������
{ 
   FILE *fp;
   FILE *p;
   printf("          %d.%d.%d            ",date.year,date.month,date.day);
   strcpy(mon[0],"January");
   strcpy(mon[1],"February");
   strcpy(mon[2],"March");
   strcpy(mon[3],"May");
   strcpy(mon[4],"May");
   strcpy(mon[5],"June");
   strcpy(mon[6],"July");
   strcpy(mon[7],"August");
   strcpy(mon[8],"september");
   strcpy(mon[9],"October");
   strcpy(mon[10],"November");
   strcpy(mon[11],"December");
   puts(mon[date.month-1]);
   for(int z=1;z<50;z++)
   {
	   printf("-");
   }
   printf("\n");
   printf("  Sun Mon Tue Wed Thu Fri Sat\n");
   for(int i=0;i<date.week;i++)
	   printf("    ");
   for(int n=1;n<day+1;n++)
   {
	   
	   if(n<10)
	   {
		   if(judge(fp,p,n))
		      printf("  %d*",n);
		   else
			   printf("   %d",n);

	   }
	   if(n>=10)
       {
		   if(judge(fp,p,n))

		      printf(" %d*",n);
		   else
			  printf("  %d",n);
	   }
	   if((n+i)%7==0)
	   {
		   printf("\n");
	   }
   }
   printf("\n");                                   //���������� ���濪ʼ�����������
   struct holiday ph,ph2;
   for(int d=0;d<31;d++)
   {

	   fp=fopen("D:\\file.txt","a+");
	   p=fopen("D:\\file2.txt","a+");
	   fscanf(fp,"%d%d%s",&ph.m,&ph.d,ph.name);
	   fscanf(p,"%d%d%d%s",&ph2.m,&ph2.whatweek,&ph2.week,ph2.name);
	   if(fp==0||p==0)
	   {
		   printf("file error\n");
		   exit(1);
	   }
	   while(!feof(fp))
	   {
		   if(date.month==ph.m)
		   {
			   if(d==ph.d)
			   {
				   printf("       %d.%d  is  %s\n",ph.m,ph.d,ph.name);
				   
			   }
		   }
			   fscanf(fp,"%d%d%s",&ph.m,&ph.d,ph.name);
	   }
	   fclose(fp);
	   while(!feof(p))
	   {
		   if(date.month==ph2.m)
		   {
			   if(d==((ph2.whatweek-1)*7+ph2.week-date.week+1))
			   {
				   printf("       %d.%d  is  %s\n",ph2.m,((ph2.whatweek-1)*7+ph2.week-date.week+1),ph2.name);
				   
			   }
		   }
			   fscanf(p,"%d%d%d%s",&ph2.m,&ph2.whatweek,&ph2.week,ph2.name);
	   }
	   fclose(p);
   }


}
int judgeday()                //�ж�һһ�����ж�����
{
   int day;
   if(date.month==4||date.month==6||date.month==9||date.month==11)
	   day=30;
   else if(date.month==2)
   {
	   if((date.year%4==0&&date.year%100!=0)||(date.year%400==0))
	       day=29;
	   else
		   day=28;
   }
   else
	   day=31;
   return day;
}
void display()               //������������ ����չʾ���� ����Ҫ¼�����
{
   week();
   int day=judgeday();
   print(day);
   printf("\n");
}
int main()
{
   
   int n=1;
   printf("����1------��ʾ��һ������    ����2------��ʾ��һ������\n����3------��ʾ��һ������    ����4------��ʾ��һ������\n����5------����              ����6------ɾ��\n����7------���´�ӡ����\n����0------�˳�\n");
   for(int z=1;z<60;z++)
   {
	   printf("-");
   }
   printf("\n");
   inputdate();
   week();
   int day=judgeday();
   print(day);
   while(n!=0)
   {
	     for(z=1;z<60;z++)
		 {
	      printf("-");
		 }
		printf("\n");
	    printf("����1------��ʾ��һ������    ����2------��ʾ��һ������\n����3------��ʾ��һ������    ����4------��ʾ��һ������\n����5------����              ����6------ɾ��\n����7------���´�ӡ����\n����0------�˳�\n");
	    printf("����ָ��");
	    scanf("%d",&n);
		switch(n)
		{
			case 0: break;
			case 1:
				{
					if(date.month!=1)
					{
						date.month--;
						display();
						
					}
					else
					{
						date.month=12;
						date.year--;
						display();
					}
				break;
				}
			case 2:
				{
					if(date.month!=12)
					{
						date.month++;
						display();
					}
					else
					{
						date.month=1;
						date.year++;
						display();
					}
				break;
				}
				
			case 3:
				{
					date.year--;
					display();
				    break;
				}
				
			case 4:
				{
					date.year++;
					display();
				    break;
				}
			case 5:
				{
					struct holiday a;
					printf("��1------����������ʽ ���¼��Ž���\n��2------����������ʽ ���µڼ������ڼ�����\n");
					printf("����ָ��");
					int v;
					FILE *fp,*p;
					scanf("%d",&v);
					if(v==1)
					{
						printf("�밴��ʽ���� ����12 12 xxx\n ");
						printf("�����µĽ���");
						fp=fopen("D:\\file.txt","a+");
						if(fp==0)
						{
							printf("file error");
							exit(1);
						}
						scanf("%d%d%s",&a.m,&a.d,a.name);
						fprintf(fp,"%d %d %s ",a.m,a.d,a.name);
						fclose(fp);
						fp=fopen("D:\\file.txt","a+");
						if(fp==0)
						{
							printf("file error");
							exit(1);
						}
						fclose(fp);
						printf("���ӳɹ�!");
						break;
						
					}
					if(v==2)
					{
						printf("�밴��ʽ���� ����12 1 1 xxx\n");
						printf("�����µĽ���");
						p=fopen("D:\\fiel2.txt","a+");
						if(p==0)
						{
							printf("file error");
							exit(1);
						}
						scanf("%d%d%d%s",&a.m,&a.whatweek,&a.week,a.name);
						fprintf(p,"%d %d %d %s ",a.m,a.whatweek,a.week,a.name);
						fclose(p);
					    p=fopen("D:\\fiel2.txt","a+");
						if(p==0)
						{
							printf("file error");
							exit(1);
						}
						fclose(p);
						printf("���ӳɹ�!");
						break;
						}
					break;
				}
			case 6:
				{
	                int q;
					int v,i=0,d;
					FILE *fp,*p;
					struct holiday s;
					struct holiday h[100];
					printf("��1------ɾ��������ʽ ���¼��Ž���\n��2------ɾ��������ʽ ���µڼ������ڼ�����\n");
					scanf("%d",&v);
					if(v==1)
					{
						printf("������ɾ����Ϣ\n");
						fp=fopen("D:\\file.txt","a+");
						scanf("%d%d%s",&s.m,&s.d,s.name);
						if(fp==0)
						{
							printf("file error");
							exit(1);
						}
						fscanf(fp,"%d%d%s",&h[i].m,&h[i].d,h[i].name);
						while(!feof(fp))
						{
							i=i+1;
							fscanf(fp,"%d%d%s",&h[i].m,&h[i].d,h[i].name);
						}
						for(int k=0;k<i;k++)
						{
							if(h[k].d==s.d&&h[k].m==s.m)
							{
								q=k;
							}
						}
						fclose(fp);
						fp=fopen("D:\\file.txt","w+");
						if(fp==0)
						{
							printf("file error");
							exit(1);
						}
						for(int j=0;j<i;j++)
						{
							if(j==q)
							{
								continue;
							}
							else
							{
								fprintf(fp,"%d %d %s ",h[j].m,h[j].d,h[j].name);
							}
						}
						fclose(fp);
						break;
					}
					if(v==2)
					{
						printf("������ɾ����Ϣ\n");
						p=fopen("D:\\file2.txt","a+");
						scanf("%d%d%d%s",&s.m,&s.whatweek,&s.week,s.name);
						if(p==0)
						{
							printf("file error");
							exit(1);
						}
						fscanf(p,"%d%d%d%s",&h[i].m,&h[i].whatweek,&h[i].week,h[i].name);
						while(!feof(fp))
						{
							i=i+1;
							fscanf(p,"%d%d%d%s",&h[i].m,&h[i].whatweek,&h[i].week,h[i].name);
						}
						
						for(int k=0;k<i-1;k++)
						{
							if(h[k].m==s.m&&h[k].whatweek==s.whatweek&&h[k].week==s.week)
							{
								q=k;
							}
						}
						fclose(p);
						fp=fopen("D:\\file2.txt","w+");
						if(p==0)
						{
							printf("file error");
							exit(1);
						}
						for(int j=0;j<i-1;j++)
						{
							if(j==q)
							{
								continue;
							}
							else
							{
							fprintf(fp,"%d %d %d %s ",h[j].m,h[j].whatweek,h[j].week,h[j].name);
							}
						}
						fclose(fp);
					}
					break;
				}
             case 7:
				{
					display();
					break;
				}
			 default :
				 {
					 printf("error!");
				 }
           }
              
	}
return 0;
}