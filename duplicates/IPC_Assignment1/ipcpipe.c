/*
   file Name  	:ipcpipe.c
   date created	:11 July 2018
   modified date	:---


 */

#include"headers.h"



int p[2];  // variable to acess the two ends of the pipe

void IpcPipeProcess(long int datasize)
{

#if debug
	printdebug("process created for pipe ");
#endif
	pipe(p);
	clock_t start , end ;
	char writebuffer[SIZE],readbuffer[SIZE];
	long count=(datasize)/(SIZE);
	double timeconsumed = 0;
	long databytes = 0;
	int c=fork();
	if(c)
	{
		/******* Writing to the pipe **********************/
		while(count--)
		{
			start = clock();
			write(p[1],&writebuffer,SIZE);
			end=clock();
			timeconsumed += (double)(end-start)/CLOCKS_PER_SEC;
			databytes += SIZE;
		}
#if debug
		printdebug("writing process terminated ");
#endif
		wait(NULL);  // waiting for the reading process to be completed 
		calculatespeed( timeconsumed , databytes,"pipe");
	}

	else
	{
		/******* Reading from the pipe **********************/
		while(count--)
		{
			start = clock();
			read(p[0],&readbuffer,SIZE);
			end=clock();
			timeconsumed += (double)(end-start)/CLOCKS_PER_SEC;
			databytes += SIZE;
		}
		calculatespeed( timeconsumed , databytes, "pipe" );
#if debug
		printdebug("reading process terminated ");
#endif
		exit(0);
	}

	return;
}
