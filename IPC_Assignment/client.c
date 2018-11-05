/*
   File Name 	:	client/sender process
date		:	9 july 2018
date modified	:	---

 */

// launching of the client/sender process as per user instructions

#include"headers.h"

void send_messagequeue(long int);
void send_fifo(long int);
void send_sharedmemory(long);

void senderprocess(char *IPC , long int DataSize)
{

	/******************** launching of the process using IPC_messagequeue ************************************/
	if(strcmp("IPC_M" , IPC)==0)
	{
#if debug
		printdebug("sender/client process is launching the IPC_M");
#endif
		send_messagequeue(DataSize);
	}

	/******************** launching of the process using IPC_fifo ***************************************/
	else if(strcmp("IPC_fifo" , IPC)==0)
	{
#if debug
		printdebug("sender/client process is launching the IPC_fifo");
#endif
		send_fifo(DataSize);
	}

	else if(strcmp("IPC_shm" , IPC)==0)
	{
#if debug
		printdebug("sender/client process is launching the IPC_shm");
#endif
		send_sharedmemory(DataSize);
	}
	else
	{
	puts(" NO such type of IPC ");
	return;
	}
}
