/*file name	:	server process
  date created 	:	9th july 2018
  date modified	:	--


 */


#include"headers.h"

void receive_messagequeue(long int);
void receive_fifo(long int);
void receive_sharedmemory(long int);
void server_socket(long);

/********** receiver process starts from here *******************/
void receiverprocess(char *IPC , long int DataSize )
{

#if debug
	puts("launching server process for  processing the data");
#endif

	/************ Launching of the process using IPC_messagequeue ********************/
	if(strcmp("IPC_M" , IPC)==0)
	{
		receive_messagequeue(DataSize);
	}

	/************ Launching of the process using IPC_fifo ********************/
	else if(strcmp("IPC_fifo" , IPC)==0)
	{
		receive_fifo(DataSize);
	}

	/************ Launching of the process using IPC_SharedMemory ********************/
	else if(strcmp("IPC_shm" , IPC)==0)
	{
		receive_sharedmemory(DataSize);
	}

	/************ Launching of the process using Socket  ********************/
	else if(strcmp("IPC_socket" , IPC)==0)
	{
		server_socket(DataSize);
	}

	else 
	{
		puts("no such type of IPC ");
	}

	return;
}
