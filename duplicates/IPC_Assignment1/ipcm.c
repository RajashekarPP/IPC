/* file name 	: ipcm.c
   date created 	: 9 july 2018
   date modified	: 13 july 2018
   version 1   	: time caluculation made in differrent way 
   version 2	: time calculation done but to change the way the data is transmitted
 */

#include"headers.h"

/******** Declaration of the message buffer ***************/
struct msgbuf 
{
	long mtype;
	char mtext[SIZE];
}v;

int msgid;

void send_messagequeue(long  int datasize)
{
	clock_t start , end ;   //variables to determine the start time and endime of single read/write operation
	long Databytes=0 ;      // To count  the total no of byte sent/received 
	double timeconsumed=0;  //Total amount of time consumed in sending/receiving data
	long count=(datasize)/SIZE;
	printf("size=%ld Bytes count=%ld\n",datasize,count);
	msgid=msgget(1,IPC_CREAT|0660);
#if debug 
	printdebug("sending data using message queue");
#endif
	strcpy(v.mtext,"ack");
	v.mtype=1;
	msgsnd(msgid,&v,strlen(v.mtext)+1,0);
	v.mtype=2;
	msgrcv(msgid,&v,100,v.mtype,0);
	for(int i=0 ;i< SIZE ; i++)
	{
		v.mtext[i]=rand();
	}
	/***************** Data sending using the messsage queue   ***************************/
	while(count--)
	{
		start=clock();
		msgsnd(msgid,&v,SIZE,0);
		end=clock();
		timeconsumed += (double)(end-start)/CLOCKS_PER_SEC;
		Databytes += SIZE;
	}
	calculatespeed( timeconsumed , Databytes , "message queue");
	return;
}

void receive_messagequeue(long  int datasize)
{
	clock_t start , end ;   //variables to determine the start time and endime of single read/write operation
	long Databytes=0 ;      // To count  the total no of byte sent/received 
	double timeconsumed=0;  //Total amount of time consumed in sending/receiving data
	long count=(datasize)/SIZE;
	printf("size=%ld Bytes  count=%ld\n",datasize,count);
	msgid=msgget(1,IPC_CREAT|0660);
#if debug 
	printdebug("sending data using message queue");
#endif
	msgrcv(msgid,&v,SIZE,1,0);
	v.mtype=2;
	msgsnd(msgid,&v,SIZE,0);
	/******************** Data  receiving using  the message queue  ************************/
	while(count--)
	{
		start=clock();
		msgrcv(msgid,&v,SIZE,0,0);
		end=clock();
		timeconsumed += (double)(end-start)/CLOCKS_PER_SEC;
		Databytes += SIZE;
	}
	calculatespeed( timeconsumed , Databytes , "message queue");
	return;
}
