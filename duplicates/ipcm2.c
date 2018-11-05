/* file name 	: ipcm.c
   date created 	: 9 july 2018
   date modified	:10 july 2018 
   version 1   	: time caluculation made in differrent way 
   version 2	:getting assurances for each time the data sent and the data received

 */

#include"headers.h"

void calculatespeed( long  , long);

struct msgbuf 
{
	long mtype;
	char mtext[100];
};

void send_messagequeue(long  int datasize)
{
	int id,id1;
	struct msgbuf v,v1;
	struct timespec starttime,endtime;
	long count=(datasize)/(sizeof(v.mtext));
	printf("size=%ld  count=%ld\n",datasize,count);
	long timeconsumed = 0 , DatabytesSent=0 ;
	id=msgget(1,IPC_CREAT|0660);
	id1=msgget(2,IPC_CREAT|0660);
#if debug 
	printdebug("sending data using message queue");
#endif
	puts("sending data using msg queue");
	strcpy(v1.mtext , "ack");
	v1.mtype=1;
	msgsnd(id1,&v1,strlen(v1.mtext)+1,0);
	strcpy(v.mtext,"**********88888888888888***************777777777*****************************99999999999999********");
	printf("%s\n",v.mtext);
	v1.mtype=2;
	while(count--)
	{
		clock_gettime(CLOCK_REALTIME,&starttime);
		msgsnd(id,&v,strlen(v.mtext)+1,0);
		clock_gettime(CLOCK_REALTIME,&endtime);
		DatabytesSent+=strlen(v.mtext)+1;
#if debug 
		printdebug("sent data using message queue");
#endif
		puts("data sent ");
		msgrcv(id1,&v1,100,2,0);
		puts("ack received ");
		timeconsumed += (endtime.tv_nsec-starttime.tv_nsec);
	}
	printf("time = %ld , data = %ld\n",timeconsumed ,DatabytesSent);
	calculatespeed( timeconsumed , DatabytesSent*1000000);
	return;
}

void receive_messagequeue(long  int datasize)
{
	int id,id1;
	struct msgbuf v,v1;
	struct timespec starttime,endtime;
	long count=(datasize)/(sizeof(v.mtext)); // no of times the buffer data to be sent
	long timeconsumed = 0 , DatabytesReceived = 0 ;
	printf("size=%ld  count=%ld\n",datasize,count);
	id=msgget(1,IPC_CREAT|0660);
	id1=msgget(2,IPC_CREAT|0660);
#if debug 
	printdebug("sending data using message queue");
#endif
	puts("receiving data using msg queue");
/*********** Waits untill the sender process is launched ******************************/
	msgrcv(id1,&v1,100,1,0);
	printf("both process launched %s\n",v1.mtext);
	while(count--)
	{
		clock_gettime(CLOCK_REALTIME,&starttime);
		msgrcv(id,&v,100,0,0);
		clock_gettime(CLOCK_REALTIME,&endtime);

		puts("data received");
		DatabytesReceived+=strlen(v.mtext)+1;
		
		v1.mtype=2;
		msgsnd(id1,&v1,100,0);

		puts("ack sent");
		timeconsumed += (endtime.tv_nsec-starttime.tv_nsec);
	}
	printf("time = %ld , data = %ld\n",timeconsumed ,DatabytesReceived);
	calculatespeed( timeconsumed , DatabytesReceived*1000000 );
	return;
}

