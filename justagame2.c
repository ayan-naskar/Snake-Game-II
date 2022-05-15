#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>
//---------------------------------------------
// REMEMBER TO NAME THE THIS FILE Justagame2.c ELSE THE PROGRAM WILL NOT BE ABLE TO CALL ITSELF
//---------------------------------------------

void initializezero(int *p)
{
	int i,j;
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			*(p+j+10*i)=0;
}

void show(int *p,int head)
{
	int i,j;
	printf("# # # # # # # # # # # #\n");
	for(i=0;i<10;i++)
	{
		printf("#");
		for(j=0;j<10;j++)
		{	
			if(*(p+j+10*i)==0)
				printf("  ");
			else
			{
				if(*(p+j+10*i)!=-1)
					if(*(p+j+10*i)==head)
						printf(" O");
					else
						printf(" o");
				else
					printf(" X");
			}
		}
		printf(" #\n");
	}
	printf("# # # # # # # # # # # #\n");
}

int gettimert()
{
	int x=500;
	char a,b;
	while(1)
	{
		system("cls");
		printf("Select the time for which the snake can live without choking\n");
		printf("<%d millisecs>",x);
		click:a=getch();
		if(a==13)
		{
			return x;
		}
		else if(a==-32)
		{
			b=getch();
			if(b==75)
				x-=500;
			else if(b==77)
				x+=500;

			if(x==0)
			{
				x=500;
				printf("\nTime cannot be 0");
				goto click;
			}
		}
	}
}

int main()
{
	int FLAGX,FLAGY,FLAG_X=1,FLAG_Y=0;
	FILE *f;
	int arr[100],i,j,trv,oldhihead;
	int head=1;
	srand(time(0));
	int x=5,y=5;
	int points=0;
	i=(int)rand()%10;
	j=(int)rand()%10;
	initializezero(arr);
	arr[10*x+y]=1;
	arr[10*i+j]=-1;
	system("cls");
	printf("Press any key to start");
	getch();
	while(1)
	{
		system("cls");
		printf("WORST SNAKE GAME EVER\n");
		printf("~~~~~~~~~~~~~~~~~~~~~\n\n");
		show(arr,head);
		FLAGX=FLAGY=0;
		if(GetAsyncKeyState(VK_UP))//(key==-32 && key2==72)
			FLAGX=-1;
		else if(GetAsyncKeyState(VK_DOWN))//key==-32 && key2==80)
			FLAGX=1;
		else if(GetAsyncKeyState(VK_RIGHT))//key==-32 && key2==77)
			FLAGY=1;
		else if(GetAsyncKeyState(VK_LEFT))//key==-32 && key2==75)
			FLAGY=-1;
		else{
			FLAGX=FLAG_X;
			FLAGY=FLAG_Y;
		}
		Sleep(100);
		FLAG_X=FLAGX;
		FLAG_Y=FLAGY;
		x=x+FLAGX;
		y=y+FLAGY;
		if(x<0)
			x=9;
		if(y<0)
			y=9;
		x%=10;
		y%=10;
		
		for(trv=0;trv<100;trv++)
		{
			if(arr[trv]>0)
				arr[trv]--;
		}
		if(x==i && y==j)
		{
			arr[10*i+j]=++head;			
			i=rand()%10;
			j=rand()%10;
			points++;
			arr[10*i+j]=-1;
			continue;
		}
		if(arr[10*x+y]>0)
		{
			system("cls");
			printf("GAME OVER!!");
			printf("\n~~~~~~~~~~~\n\n");
			show(arr,head);			
			printf("\nYour snake ate itself!");
			printf("\nYour Score is: %d",head);
			goto thatplace;
		}

		arr[10*x+y]=head;
	}
	thatplace:f=fopen("Scoreboard.txt","r");
	if(f==NULL)
	{
		f=fopen("Scoreboard.txt","w");
		fprintf(f,"%d",head);
		printf("\nThis is your new high score: %d",head);
		fclose(f);
	}
	else
	{
		fscanf(f,"%d",&oldhihead);
		if(head>oldhihead)
		{
			printf("\nThis is your new high score: %d",head);
			fprintf(f,"%d",head);
		}
		else
		{
			printf("\nYour old Best Score ever was: %d",oldhihead);
		}
		fclose(f);
	}
	Sleep(8000);
	printf("\n\n\nPress any key to continue...");
	getch();
	system("Justagame2.exe 5434 localhost");
}
