/*
   File Name    :   main.c
author       :	 raja
date created :	6 july
modified     :



launching the process

project file is made using the make file which is the final executable file

HOW TO LAUNC THE PROCESS/PROJECT

./project  sender/receiver  IPC_mechanism  datasize		

IPC_M 	 : messagequeue
IPC_fifo : fifo
IPC-shm  : shared memory
IPC_pipe : pipe
 */


/*********************main function starts from here *********************************/

#include"headers.h"

#define debug 1		// 0 indicates no debugging 1 to start debbuging

#define MB  1 		// to indicate that data is in MB  default data size is in KB


void printdebug(char *);
void senderprocess( char * , long int );
void receiverprocess( char * , long int);
void IpcPipeProcess(long);

void  main(int argc , char **argv)
{

	/**************** Launching of the process for pipe ****************************/
	if( argc == 3)
	{
		long int datasize;
		datasize=atoi(argv[2])*1000;
#if MB
		datasize *= 1000;
#endif
		if(strcmp(argv[1],"IPC_pipe")==0)
			IpcPipeProcess(datasize);
		else
		{
			puts("launching format is :\n\n./project  sender/receiver  IPC_M/IPC_fifo/IPC_shm  datasize in KB");
			puts("launching format for pipe  is :\n ./project  IPC_pipe  datasize in KB");
		}
		return ;
	}
	if ( argc != 4)
	{
		puts("launching format is :\n\n./project  sender/receiver  IPC_M/IPC_fifo/IPC_shm  datasize in KB");
		puts("launching format for pipe  is :\n\n./project  IPC_pipe  datasize in KB");
		return ;
	}

	long int datasize;
	datasize=atoi(argv[3])*1000;
#if MB
	datasize *= 1000;
#endif

	/**************** Launching of the process for IPC other than pipe ****************************/

	if(strcmp(argv[1],"sender")==0)
	{
#if debug
		printdebug("sender/client  process is launched");
#endif
		senderprocess( argv[2] , datasize ); //arguments is to inform the process to use which one of the IPC's and datasize to be transmitted
	}
	else if(strcmp(argv[1],"receiver")==0)
	{
#if debug
		printdebug("receiver/server process is launched");
#endif
		receiverprocess( argv[2] , datasize ); // argument is to inform the process to use which one of the IPC's
	}
	else
	{
		printf("eror in creating the asked process");
	}

	return ;
}


void printdebug(char *msg)
{
	printf("%s\n",msg);
}

