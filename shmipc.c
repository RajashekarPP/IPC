#include<sys/sem.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/ipc.h>

main()
{
	if(fork())
	{	
		int id;
		char *ptr,cnt=0;
		id=shmget(1,50,IPC_CREAT|0660);
		//printf("id=%d in process  %d \n",id,getpid());
		ptr=shmat(id,NULL,0);
		srand(getpid());
		while(cnt!=10)
		{
			ptr[cnt++]=rand()%100;
		}
		wait(NULL);
		printf(" min=%d   max = %d \n",ptr[10],ptr[11]);
		exit(0);

	}
	else
	{
		usleep(500);
		int id,max,min,i;
		char *ptr,cnt=0,buf[10];
		id=shmget(1,50,IPC_CREAT|0660);
		printf("id=%d in process  %d \n",id,getpid());
		ptr=shmat(id,NULL,0);
		while(cnt!=10)
		{
			buf[cnt]=ptr[cnt];
			cnt++;
		}
		max=buf[0];
		min=buf[0];
		for(i=1;i<10;i++)
		{
			if(min>buf[i])
				min=buf[i];
			if(max<buf[i])
				max=buf[i];
		}
		ptr[10]=min;
		ptr[11]=max; 
		exit(0);
	}
}

