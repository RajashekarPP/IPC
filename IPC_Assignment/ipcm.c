/* file name 	: ipcm.c
   date created 	: 9 july 2018
   date modified	: --
   version 1   	: time caluculation made in differrent way 
   version 2	: time calculation done but to change the way the data is transmitted

 */
#include"headers.h"

void calculatespeed( double , long);

struct msgbuf 
{
	long mtype;
	char mtext[100];
};


void send_messagequeue(long  int datasize)
{
	int id;
	struct msgbuf v,v1;
	clock_t start , end;
	long count=(datasize)/(sizeof(v.mtext));
	printf("size=%ld  count=%ld\n",datasize,count);
	double timeconsumed = 0 ;
	long  DatabytesSent=0 ;
	id=msgget(1,IPC_CREAT|0660);
#if debug 
	printdebug("sending data using message queue");
#endif
	strcpy(v.mtext,"ack");
	v.mtype=1;
	msgsnd(id,&v,strlen(v.mtext)+1,0);
	v.mtype=2;
	msgrcv(id,&v,100,v.mtype,0);
	strcpy(v.mtext,"**********88888888888888***************777777777*****************************99999999999999********");
	start=clock();
	/***************** Data sending using the messsage queue   ***************************/
	while(count--)
	{
		msgsnd(id,&v,100,0);
		DatabytesSent+=strlen(v.mtext);
	}
	end=clock();
	timeconsumed += (double)(end-start)/CLOCKS_PER_SEC;
	calculatespeed( timeconsumed , DatabytesSent);
	return;
}

void receive_messagequeue(long  int datasize)
{
	int id;
	struct msgbuf v;
	long count=(datasize)/(sizeof(v.mtext)); // no of times the buffer data to be sent
	double timeconsumed = 0 ;
	clock_t start , end;
	long DatabytesReceived = 0 ;
	printf("size=%ld  count=%ld\n",datasize,count);
	id=msgget(1,IPC_CREAT|0660);
#if debug 
	printdebug("sending data using message queue");
#endif
	msgrcv(id,&v,100,1,0);
	v.mtype=2;
	msgsnd(id,&v,100,0);
	start=clock();
	/******************** Data  receiving using  the message queue  ************************/
	while(count--)
	{
		msgrcv(id,&v,100,0,0);
		DatabytesReceived+=strlen(v.mtext);
	}
	end=clock();
	timeconsumed += (double)(end-start)/CLOCKS_PER_SEC;
	calculatespeed( timeconsumed , DatabytesReceived );

	return;
}

