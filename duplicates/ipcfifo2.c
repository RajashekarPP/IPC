/*
   file name  : ipcfifo.c 
   date created : 9 july 2018
   --version 1    : synchronization is not necessary as these provide synchronization
   date modified : --
author  : raja shekar 

 */

#include"headers.h"

void calculatespeed(long , long);

/**************function to send data using IPC fifo mechanism*****************************/

void send_fifo(long datasize)
{
	puts("sending data using the fifo mechanism");
	int fd;
	struct timespec starttime , endtime;
	long DatabytesSent=0 , timeconsumed=0;
	char writebuffer[100]="@@@@@@@@@@2222222222$$$$$$$$$$2222222222**********2222222222**********2222222222%%%%%%%%%%2222222222";
	long count=(datasize)/sizeof(writebuffer);
#if debug
	printdebug("sending using fifo");
#endif
	printf("data size = %ld  count =%ld \n",datasize , count);
	mkfifo("fifo1",IPC_CREAT|0660);
	perror("fifo1");
	fd=open("fifo1",O_WRONLY);

	clock_gettime(CLOCK_REALTIME , &starttime);
	puts("started to write the data");
	while(count--)
	{
		write(fd,writebuffer,100);
		DatabytesSent += strlen(writebuffer);
	}
	clock_gettime(CLOCK_REALTIME , &endtime);
	timeconsumed += ( endtime.tv_sec - starttime.tv_sec )*1000000;
	calculatespeed( timeconsumed , DatabytesSent );
	return;
}


/**************function to receive data using IPC fifo mechanism*****************************/

void receive_fifo(long datasize)
{
	puts("receiving the data using fifo mechanism");
	int fd,fd1;
	char readbuffer[100],ack[10];
	struct timespec starttime , endtime;
	long DatabytesReceived=0 , timeconsumed=0;
	long count=(datasize)/sizeof(readbuffer);
#if debug
	printdebug("receiving data using fifo");
#endif
	printf("data size = %ld  count =%ld \n",datasize*1000 , count);
	mkfifo("fifo1",IPC_CREAT|0660);
	perror("fifo1");
	fd=open("fifo1",O_RDONLY);

	clock_gettime(CLOCK_REALTIME , &starttime);
	puts("started to read the data");
	while(count--)
	{
		read(fd,readbuffer,100);
		DatabytesReceived+=strlen(readbuffer);
	}
	clock_gettime(CLOCK_REALTIME , &endtime);
	timeconsumed+=( endtime.tv_sec - starttime.tv_sec )*1000000;
	calculatespeed( timeconsumed , DatabytesReceived );
	return;
}

