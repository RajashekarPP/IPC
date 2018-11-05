#include"headers.h"

struct msgbuf 
{

	long  mtype;
	char mtext[20];

};

int main()
{
	int id;
	struct msgbuf v;
	id=msgget(10,IPC_CREAT|0660);
	printf("msg id = %d\n",id);
	v.mtype=1;
	while(1)
	{
		printf("enter data to be sent \n");
		fgets(v.mtext,20,stdin);
		msgsnd(id,&v,20,0);
		printf("msg sent is %s\n",v.mtext);
	}
}
