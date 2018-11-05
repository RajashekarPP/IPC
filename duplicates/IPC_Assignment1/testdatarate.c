#include"headers.h"

int main()
{
	char buffer1[1000] , buffer2[1000];
	clock_t start , end;
	double time;

	start = clock();
	strncpy(buffer1 , buffer2 ,1000);
	end = clock();
	time = (double)(end - start)/CLOCKS_PER_SEC ;
	printf("time = %lf \n",time);
sleep(1);	
	start = clock();
	strncpy(buffer1 , buffer2 ,100);
	end = clock();
	time = (double)(end - start)/CLOCKS_PER_SEC ;
	printf("time = %lf \n",time);
	
sleep(1);	
	
	start = clock();
	strncpy(buffer1 , buffer2 ,1000);
	end = clock();
	time = (double)(end - start)/CLOCKS_PER_SEC ;
	printf("time = %lf \n",time);
	
	
	return 0;

}
