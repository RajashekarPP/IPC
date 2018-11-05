/*
file Name  	:ipcpipe.c
date created	:11 July 2018
modified date	:---


*/

#include"headers.h"

#define SIZE 100

void calculatespeed( double , long );
int p[2];

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
	strcpy(writebuffer,"11111111112222222222223333333******************/////////////////////////+++++++++++++--------------");
	int c=fork();

	if(c)
	{
		start = clock();
	/******* Writing to the pipe **********************/
		while(count--)
		{
			write(p[1],&writebuffer,100);
			databytes += strlen(writebuffer);
		}
		end=clock();
		timeconsumed += (double)(end-start)/CLOCKS_PER_SEC;
#if debug
		printdebug("writing process terminated ");
#endif
		wait(NULL);  // waiting for the reading process to be completed 
		calculatespeed( timeconsumed , databytes );
	}

	else
	{
		start = clock();
	/******* Reading from the pipe **********************/
		while(count--)
		{
			read(p[0],&readbuffer,100);
			databytes += strlen(readbuffer);
		}
		end = clock();
		timeconsumed += (double)(end-start)/CLOCKS_PER_SEC;
		calculatespeed( timeconsumed , databytes );
#if debug
		printdebug("reading process terminated ");
#endif
		exit(0);
	}


	return;

}
