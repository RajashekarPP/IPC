/*
   file name            : ipcshm.c
   date created		: 9 july 2018
   date modified	:10 july 2018   written codde to find the time consumed for sending and receiving
  Author		: raja shekar
 */

#include"headers.h"


int semid , shmid ;   // semaphore id and shared memory id respectively
struct sembuf v ;

/******** Launching of the process to SEND data using IPC_Shared Memory **********************/

void send_sharedmemory(long  int datasize)
{
	clock_t start , end ;   //variables to determine the start time and endime of single read/write operation
	long Databytes=0 ;      // To count  the total no of byte sent/received 
	double timeconsumed=0;  //Total amount of time consumed in sending/receiving data
	long count=(datasize)/(SIZE);
	char *temp=NULL , sendbuffer[SIZE];
	shmid=shmget(1,SIZE,IPC_CREAT|0660);
	temp=shmat(shmid,NULL,0);
	semid=semget(1,2,IPC_CREAT|0660);
	v.sem_op=0;
	v.sem_num=0;
	v.sem_flg=0;
	for(int i=0 ; i< SIZE ; i++)
	{
		sendbuffer[i]=rand();
	}
#if debug 
	printdebug("sending data using shared memory");
#endif
	printf("count = %ld  data = %ld \n",count  ,datasize);
	semctl(semid,1,SETVAL,1); // semaphore to stop/start reading if set 1 no reading is done
	semctl(semid,0,SETVAL,0); // semaphore to stop/start writing if set 1 no writing is done
	while(count--)
	{
		semop(semid,&v,1);
		semctl(semid,0,SETVAL,1);	// making read process enable to read data if launched first	
		start=clock();
		strncpy(temp , sendbuffer , SIZE);
		end=clock();
		semctl(semid,1,SETVAL,0);
		timeconsumed += (double)(end-start)/CLOCKS_PER_SEC;
		Databytes += SIZE;
	}
	shmdt(temp);
	calculatespeed( timeconsumed , Databytes , "sharedmemory");
	return;
}

/******** Launching of the process to RECEIVE  data using IPC_Shared Memory **********************/
void receive_sharedmemory(long  int datasize)
{

	clock_t start , end ;   //variables to determine the start time and endime of single read/write operation
	long Databytes=0 ;      // To count  the total no of byte sent/received 
	double timeconsumed=0;  //Total amount of time consumed in sending/receiving data
	long count=(datasize)/(SIZE);
	char receivebuffer[SIZE] , *temp=NULL;
	semid=semget(1,2,IPC_CREAT|0660);
	v.sem_op=0;
	v.sem_num=1;
	v.sem_flg=0;
	shmid=shmget(1,SIZE,IPC_CREAT|0660);
	temp=shmat(shmid,NULL,0);
#if debug 
	printdebug("receiving data using shared memory");
#endif
	printf("count = %ld  data = %ld Bytes \n",count  ,datasize);
	while(count--)
	{
		semop(semid,&v,1);
		semctl(semid,1,SETVAL,1);
		start=clock();
		strncpy( receivebuffer, temp , SIZE);
		end=clock();
		timeconsumed += (double)(end-start)/CLOCKS_PER_SEC;
		semctl(semid,0,SETVAL,0);		
		Databytes += SIZE;
	}
	shmdt(temp);
	calculatespeed( timeconsumed , Databytes , "sharedmemory");
	return;
}

