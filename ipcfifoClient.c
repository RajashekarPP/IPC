#include"headers.h"

int main()
{
	int fd1,fd2;
	char r[5],w[30];
	if(mkfifo("fifo1",0660)==-1)
		perror("fifo1");	
	fd1=open("fifo1",O_WRONLY);

	if(mkfifo("fifo2",0660)==-1)
		perror("fifo2");	
	fd2=open("fifo2",O_RDONLY);

	while(1)
	{	
		puts("enter msg to send to server");
		fgets(w,30,stdin);
		write(fd1,w,30);
		read(fd2,r,5);
		if(strncmp(r,"stop",4)==0)
			break;
	}
	close(fd1);
	close(fd2);
	exit(0);
}
