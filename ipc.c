
#include<stdio.h>
#include<sys/msg.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>

struct msgbuf
{
    
     int mtype;
     char mtext[200];   
};


int main(void)
{
    
    if(fork())
    {
        int id ;
        struct msgbuf v;
        id=msgget(1,IPC_CREAT|0660);
	while(1)
	{	
		puts("enter data to be sent");
		fgets(v.mtext,200,stdin);
        	printf("message sent is \n%s  \n",v.mtext);
        	if(strstr(v.mtext,"quit"))
		{
			msgsnd(id,&v,20,0);
			break; 
        	}
		msgsnd(id,&v,20,0);
 	}
	wait(NULL);      	
	exit(0);
    }
    
    else
    {
        int id;
        struct msgbuf v;
        id=msgget(1,IPC_CREAT|0660);

	while(1)
	{
	        msgrcv(id,&v,200,0,0);
        	printf("message received is \n%s\n",v.mtext);
	
		 if(strstr(v.mtext,"start"))
		  {
			puts("server processing");
		 }

	        else if(strstr(v.mtext,"quit"))
		 {
			puts("server exiting");
			break;
		 }

	}
	exit(0);
    }
    
    
    return 0;
}

