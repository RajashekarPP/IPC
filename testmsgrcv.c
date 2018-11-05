#include"headers.h"
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>


struct msgbuf 
{
	long mtype;
	char mtext[20];

};

int main()
{
	int id;
	struct msgbuf v;
	id=msgget(10,IPC_CREAT|0660);
	printf("msg id= %d\n",id);
	v.mtype=1;
	while(1)
	{
//		v.mtype=1;
		msgrcv(id,&v,20,v.mtype,0);
		printf("msg recived is %s\n",v.mtext);
	}
}
