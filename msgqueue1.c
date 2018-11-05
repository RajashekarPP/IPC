
#include<stdio.h>
#include<sys/msg.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

struct msgbuf
{

	int mtype;
	char mtext[200];   
};


int main(void)
{
	if(fork())
	{
		int id,id1;
		struct msgbuf v,v1;
		id=msgget(1,IPC_CREAT|0660);
		id1=msgget(2,IPC_CREAT|0660);
		while(1)
		{	
			puts("In sending process");
			puts("enter data to be sent");
			fgets(v.mtext,50,stdin);
			msgsnd(id,&v,50,0);
			msgrcv(id1,&v1,20,0,0);
			puts("msg from server process is");
			printf("%s\n",v1.mtext);
			if(!strcmp(v1.mtext,"stop"))
				break;
		}
		wait(NULL);      	
		exit(0);
	}

	else
	{
		int id,id1;
		struct msgbuf v,v1;
		id=msgget(1,IPC_CREAT|0660);
		id1=msgget(2,IPC_CREAT|0660);
		while(1)
		{
			msgrcv(id,&v,200,0,0);
			puts("in receiving process");
			printf("message received is \n%s\n",v.mtext+5);
		//	if(strstr(v.mtext,"start"))
			if(strncmp(v.mtext,"start",5)==0)
			{
				puts("processing the data");
			}
			puts("type \"stop\" to stop receiving data else contd");
			scanf("%[^\n]s",v1.mtext);
			msgsnd(id1,&v1,20,0);
			if(!strcmp(v1.mtext,"stop"))
				break;
		}
		exit(0);
	}
	return 0;
}

