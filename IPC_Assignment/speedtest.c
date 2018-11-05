/* fille Name 	:	speedtest.c
date created 	:	9 july 2018
date modified	:	--

*/

#include"headers.h"

void calculatespeed(double timeconsumed , long datasize)
{
	double speed = ((double)(datasize)/(double)timeconsumed)/1000000;
	printf("\ndata speed in IPC = %lf Mbps\n" , speed);
	return;
}

