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
struct Date{                          //定义日期结构体
	int day;
	int month;
	int year;
	int week;                         //为了方便week代表这个月第一天是周几
}date;
char mon[12][12];                      //定义一个数组 存储月份
void inputdate()                       //输入日期
{
	
	printf("请输入日期\n");
	scanf("%d.%d.%d",&date.year,&date.month,&date.day);
}
void week()                           //计算星期
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
int judge(FILE *fp,FILE *p,int i)                            //判断是否是节日
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

void print(int day)                             //输出日历
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
   printf("\n");                                   //日历输出完毕 下面开始输出节日名称
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
int judgeday()                //判断一一个月有多少天
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
void display()               //包含两个函数 可以展示日历 不需要录入参数
{
   week();
   int day=judgeday();
   print(day);
   printf("\n");
}
int main()
{
   
   int n=1;
   printf("输入1------显示上一月月历    输入2------显示下一月月历\n输入3------显示上一年月历    输入4------显示下一年月历\n输入5------新增              输入6------删除\n输入7------重新打印表格\n输入0------退出\n");
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
	    printf("输入1------显示上一月月历    输入2------显示下一月月历\n输入3------显示上一年月历    输入4------显示下一年月历\n输入5------新增              输入6------删除\n输入7------重新打印表格\n输入0------退出\n");
	    printf("输入指令");
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
					printf("按1------新增节日样式 几月几号节日\n按2------新增节日样式 几月第几个星期几节日\n");
					printf("输入指令");
					int v;
					FILE *fp,*p;
					scanf("%d",&v);
					if(v==1)
					{
						printf("请按格式输入 例如12 12 xxx\n ");
						printf("输入新的节日");
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
						printf("添加成功!");
						break;
						
					}
					if(v==2)
					{
						printf("请按格式输入 例如12 1 1 xxx\n");
						printf("输入新的节日");
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
						printf("添加成功!");
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
					printf("按1------删除节日样式 几月几号节日\n按2------删除节日样式 几月第几个星期几节日\n");
					scanf("%d",&v);
					if(v==1)
					{
						printf("请输入删除信息\n");
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
						printf("请输入删除信息\n");
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