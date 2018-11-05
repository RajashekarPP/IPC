#include"headers.h"

int main()
{
	int fd1,fd2;
	char r[30],w[5];
	if(fork())
	{
		if(mkfifo("fifo1",0660)==-1)
			perror("fifo1");	
		fd1=open("fifo1",O_RDONLY);
		if(mkfifo("fifo2",0660)==-1)
			perror("fifo1");	
		fd2=open("fifo2",O_WRONLY);

		while(1)
		{		
			read(fd1,r,30);
			printf("string from the client is \n%s\n",r);
			if(strncmp(r,"start",5)==0)
			{
				puts("processing the message");
				printf("message is\n%s\n",r+5);
			}
			printf("enter \"stop\" to receive data\n");
			fgets(w,5,stdin);	
			write(fd2,w,5);
			if(strcmp(w,"stop")==0)
				break;
		}
		exit(0);
	}
}
