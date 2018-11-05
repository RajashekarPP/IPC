#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/types.h>
#include"headers.h"

int complete=0;
int p[6];
int cnt=6;
void isr(int n)
{
	if(complete==0)
	{
		int v=0;
		printf("child returned\n");
		waitpid(-1,&v,WNOHANG);
		v=v>>8;
		printf("child %d returned safely\n",v);
		p[v]=0;
	}
}

void dead(int n)
{
	puts("alarm time completed");
	complete =1;
	int i=0;
	int v;
	printf("%d %d %d %d %d %d \n",p[0],p[1],p[2],p[3],p[4],p[5]);
	for(i=1;i<6;i++)
	{
		while(p[i])
		{
			kill(p[i],9);
			waitpid(-1,&v,0);
			printf("child %d abruptly terminated by parent \n",i);
			break;
		}
	}
	puts("ALL child's killed");

}

int main ()
{
	int i;
	signal(17,isr);
	signal(14,dead);
	alarm(10);
	for (i = 1; i < 6; i++)
	{
		if ((p[i]=fork()) == 0)
		{

			printf ("in %d child pid %d\n", i, getpid ());
			int t;
			srand(getpid());
			t=rand()%20+1;
			printf("child %d delay %d sec\n",i,t);
			sleep(t);
			exit(i);
		}
	}
	p[0]=getpid();
	printf ("in parent pid %d \n", getpid ());
	printf("%d %d %d %d %d %d \n",p[0],p[1],p[2],p[3],p[4],p[5]);

	while(1);

}
