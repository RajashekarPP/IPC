/* fille Name 	:	speedtest.c
date created 	:	9 july 2018
date modified	:	--

*/

#include"headers.h"

void calculatespeed(double timeconsumed , long datasize , const char *IPC)
{
	double speed = ((double)(datasize)/(double)timeconsumed)/(1024*1024);
	printf("time = %lf  data = %ld \n",timeconsumed , datasize/(1024*1024)); 
	printf("data speed in IPC %s = %lf Mbps\n\n" ,IPC , speed);
	return;
}

