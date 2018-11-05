/*
   file name  		: ipcfifo.c 
   date created 	: 9 july 2018
   --version 1    	: synchronization is not necessary as these provide synchronization
   date modified 	: 10 july 2018  modified the way of time caluculated for data processing   
author		  	: raja shekar 

 */

#include"headers.h"


int fd;			//file descriptor to acess the fifo

/**************function to send data using IPC fifo mechanism*****************************/

void send_fifo(long datasize)
{
	clock_t start , end ;   //variables to determine the start time and endime of single read/write operation
	long Databytes=0 ;      // To count  the total no of byte sent/received 
	double timeconsumed=0;  //Total amount of time consumed in sending/receiving data
	char writebuffer[SIZE]="@@@@@@222222****22222**********2222222%%%%%%%%*2222222";
	long count=(datasize)/SIZE;
#if debug
	printdebug("sending data  using fifo");
#endif
	printf("data size = %ld Bytes  count =%ld \n",datasize , count);
	mkfifo("fifo1",IPC_CREAT|0660);
	perror("sender fifo1");
	fd = open("fifo1",O_WRONLY);
	if(fd==-1)
	{
		perror("fifo1");
	}
	while(count--)
	{
		/*************** writing data into fifo  *****************/
		start = clock();
		write(fd,writebuffer,SIZE);
		end=clock();
		timeconsumed += (double)(end-start)/CLOCKS_PER_SEC;
		Databytes += SIZE;
	}
	calculatespeed( timeconsumed , Databytes , "fifo" );
	return;
}


/**************function to receive data using IPC fifo mechanism*****************************/

void receive_fifo(long datasize)
{
	clock_t start , end ;   //variables to determine the start time and endime of single read/write operation
	long Databytes=0 ;      // To count  the total no of byte sent/received 
	double timeconsumed=0;  //Total amount of time consumed in sending/receiving data
	char readbuffer[SIZE];
	long count=(datasize)/SIZE;
#if debug
	printdebug("receiving data using fifo");
#endif
	printf("data size = %ld Bytes  count =%ld \n",datasize , count);
	mkfifo("fifo1",IPC_CREAT|0660);
	perror("receiver fifo1");
	fd=open("fifo1",O_RDONLY);
	if(fd==-1)
	{
		perror("fifo1");
	}
	while(count--)
	{
		/*********** reading data from fifo *****************/
		start=clock();
		read(fd,readbuffer,SIZE);
		end=clock();
		timeconsumed +=(double)(end-start)/CLOCKS_PER_SEC;
		Databytes += SIZE;
	}
	calculatespeed( timeconsumed , Databytes , "fifo" );
	return;
}

