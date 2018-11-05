#include<time.h>
#include<stdio.h>
#include<sys/msg.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>


struct msgbuf
{

	long mtype;
	char mtext[200];   
};


int main(void)
{

	if(fork())
	{
		int id;
		struct msgbuf v;
		struct timespec t;
		id=msgget(1,IPC_CREAT|0660);
		while(1)
		{	
			puts("In sending process");
			puts("enter data to be sent");
			fgets(v.mtext,200,stdin);
			printf("message sent is \n%s  \n",v.mtext);
			clock_gettime(CLOCK_REALTIME,&t);
			msgsnd(id,&v,200,0);
			printf("%ld\n",t.tv_nsec);
			msgrcv(id,&v,20,1,0);
			if(!strcmp(v.mtext,"stop"))
				break;
		}
		wait(NULL);      	
		exit(0);
	}

	else
	{
		int id;
		struct msgbuf v;
		struct timespec t;
		id=msgget(1,IPC_CREAT|0660);
		while(1)
		{
			puts("in receiving process");
			msgrcv(id,&v,200,0,0);
			clock_gettime(CLOCK_REALTIME,&t);
			printf("%ld\n",t.tv_nsec);
			printf("message received is \n%s\n",v.mtext);
			puts("type \"stop\" to stop receiving data else contd");
			scanf("%s",v.mtext);
			v.mtype=1;
			msgsnd(id,&v,20,0);
			if(!strcmp(v.mtext,"stop"))
				break;
		}
		exit(0);
	}


	return 0;
}

