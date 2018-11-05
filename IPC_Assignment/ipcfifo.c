/*
   file name  		: ipcfifo.c 
   date created 	: 9 july 2018
   --version 1    	: synchronization is not necessary as these provide synchronization
   date modified 	: 10 july 2018  modified the way of time caluculated for data processing   
author		  	: raja shekar 

 */

#include"headers.h"

void calculatespeed(double , long);

/**************function to send data using IPC fifo mechanism*****************************/

void send_fifo(long datasize)
{
	puts("sending data using the fifo mechanism");
	int fd;
	clock_t start , end ;
	long DatabytesSent=0 ;
	double timeconsumed=0;
	char writebuffer[100]="@@@@@@@@@@2222222222$$$$$$$$$$2222222222**********2222222222**********2222222222%%%%%%%%%%2222222222";
	long count=(datasize)/sizeof(writebuffer);
#if debug
	printdebug("sending using fifo");
#endif
	printf("data size = %ld  count =%ld \n",datasize , count);
	mkfifo("fifo1",IPC_CREAT|0660);
	perror("fifo1");
	fd = open("fifo1",O_WRONLY);
	start = clock();
	while(count--)
	{
	/*************** writing data into fifo  *****************/
		write(fd,writebuffer,100);
		DatabytesSent += strlen(writebuffer);
	}
	end=clock();
	timeconsumed += (double)(end-start)/CLOCKS_PER_SEC;
	calculatespeed( timeconsumed , DatabytesSent );
	return;
}


/**************function to receive data using IPC fifo mechanism*****************************/

void receive_fifo(long datasize)
{
	puts("receiving the data using fifo mechanism");
	int fd;
	char readbuffer[100];
	clock_t start , end ;
	long DatabytesReceived=0 ;
	double timeconsumed=0;
	long count=(datasize)/sizeof(readbuffer);
#if debug
	printdebug("receiving data using fifo");
#endif
	printf("data size = %ld  count =%ld \n",datasize , count);
	mkfifo("fifo1",IPC_CREAT|0660);
	perror("fifo1");
	fd=open("fifo1",O_RDONLY);
	start=clock();
	while(count--)
	{
	/*********** reading data from fifo *****************/
		read(fd,readbuffer,100);
		DatabytesReceived += strlen(readbuffer);
	}
	end=clock();
	timeconsumed +=(double)(end-start)/CLOCKS_PER_SEC;
	calculatespeed( timeconsumed , DatabytesReceived );
	return;
}

