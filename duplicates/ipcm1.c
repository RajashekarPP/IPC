/* file name 	: ipcm.c
date created 	: 9 july 2018
date modified	: --
version 1   	: time caluculation made in differrent way 
version 2	: time calculation done but to change the way the data is transmitted

*/
#include"headers.h"

//void calculatespeed( long , long , long);

void calculatespeed( long  , long);
struct msgbuf 
{
	long mtype;
	char mtext[100];
};


void send_messagequeue(long  int datasize)
{
	int id;
	struct msgbuf v,v1;
	struct timespec starttime,endtime;
	long count=(datasize)/(sizeof(v.mtext));
	printf("size=%ld  count=%ld\n",datasize,count);
	long timeconsumed = 0 , DatabytesSent=0 ;
	id=msgget(1,IPC_CREAT|0660);
#if debug 
	printdebug("sending data using message queue");
#endif
	strcpy(v.mtext,"ack");
	v.mtype=1;
	msgsnd(id,&v,strlen(v.mtext)+1,0);
	strcpy(v.mtext,"**********88888888888888***************777777777*****************************99999999999999********");
	while(count--)
	{
		clock_gettime(CLOCK_REALTIME,&starttime);
		msgsnd(id,&v,100,0);
		clock_gettime(CLOCK_REALTIME,&endtime);
		DatabytesSent+=strlen(v.mtext);
		printf("sent  ");
		timeconsumed+=(endtime.tv_nsec-starttime.tv_nsec);
	}
	calculatespeed( timeconsumed , DatabytesSent);
	return;
}

void receive_messagequeue(long  int datasize)
{
	int id;
	struct msgbuf v;
	struct timespec starttime,endtime;
	long count=(datasize)/(sizeof(v.mtext)); // no of times the buffer data to be sent
	long timeconsumed = 0 , DatabytesReceived = 0 ;
	printf("size=%ld  count=%ld\n",datasize,count);
	id=msgget(1,IPC_CREAT|0660);
#if debug 
	printdebug("sending data using message queue");
#endif
	msgrcv(id,&v,100,1,0);
	printf("%s\n",v.mtext);
	while(count--)
	{
		clock_gettime(CLOCK_REALTIME,&starttime);
		msgrcv(id,&v,100,0,0);
		clock_gettime(CLOCK_REALTIME,&endtime);
		DatabytesReceived+=strlen(v.mtext);
		timeconsumed+=(endtime.tv_nsec-starttime.tv_nsec);
	}
	calculatespeed( timeconsumed , DatabytesReceived );
//	calculatespeed( starttime.tv_sec , endtime.tv_sec , DatabytesReceived );

	return;
}

