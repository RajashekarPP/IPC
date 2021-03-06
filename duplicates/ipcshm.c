/*
   file name            : ipcshm.c
   date created		: 9 july 2018
   date modified	:10 july 2018   written codde to find the time consumed for sending and receiving

*/

#include"headers.h"
#define SIZE 100  // Indicates the size of the buffers and the shared memory used

void calculatespeed( double , long);


/******** Launching of the process to SEND data using IPC_Shared Memory **********************/

void send_sharedmemory(long  int datasize)
{
	int semid;
	semid=semget(1,2,IPC_CREAT|0660);
	struct sembuf v ;
	v.sem_op=0;
	v.sem_num=0;
	v.sem_flg=0;
	clock_t start , end;
	char *temp=NULL , sendbuffer[SIZE];
	int id;
	id=shmget(1,SIZE,IPC_CREAT|0660);
	temp=shmat(id,NULL,0);
	double timeconsumed = 0 ;
	long DatabytesSent=0;
	strcpy(sendbuffer,"2222awes fsad fsd fsdf sdfsdfsdfsdfweee#########$$$$$$$$$$$%%%%%%%%%%%^^^^^^^^^^^^&&&sdfsdfsdfsd435");
	long count=(datasize)/SIZE;
#if debug 
	printdebug("sending data using shared memory");
#endif
	puts("sending data using shm");
	printf("count = %ld  data = %ld \n",count  ,datasize);
	semctl(semid,1,SETVAL,1);
	semctl(semid,0,SETVAL,0);
	printf("reader process is launched\n");
	start=clock();
	while(count--)
	{
		semop(semid,&v,1);
		semctl(semid,0,SETVAL,1);	// making read process enable to read data if launched first	
		strcpy(temp,sendbuffer);
		semctl(semid,1,SETVAL,0);
		DatabytesSent += strlen(sendbuffer);
	}
	end=clock();
	timeconsumed += (double)(end-start)/CLOCKS_PER_SEC;
	shmdt(temp);
	calculatespeed( timeconsumed , DatabytesSent );
	return;
}

/******** Launching of the process to RECEIVE  data using IPC_Shared Memory **********************/
void receive_sharedmemory(long  int datasize)
{
	int semid , id , buffersize;
	char receivebuffer[SIZE] , *temp=NULL;
	double timeconsumed=0 ;
	long DatabytesReceived=0 ; 
	clock_t start , end;
	long count=(datasize)/(SIZE);
	struct sembuf v , v1;
	semid=semget(1,2,IPC_CREAT|0660);
	v.sem_op=0;
	v.sem_num=1;
	v.sem_flg=0;

	id=shmget(1,SIZE,IPC_CREAT|0660);
	temp=shmat(id,NULL,0);
#if debug 
	printdebug("receiving data using shared memory");
#endif
	puts("receiving data using shm");
	printf("count = %ld  data = %ld \n",count  ,datasize);

	printf("receiver receiving the data\n");
	start=clock();
	while(count--)
	{
		semop(semid,&v,1);
		semctl(semid,1,SETVAL,1);
		strcpy(receivebuffer,temp);
		semctl(semid,0,SETVAL,0);		
		DatabytesReceived += strlen(receivebuffer);
	}
	end=clock();
	timeconsumed += (double)(end-start)/CLOCKS_PER_SEC;
	shmdt(temp);
	calculatespeed( timeconsumed , DatabytesReceived );
	return;
}

