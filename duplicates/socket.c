/*
   File Name	 	: socket.c
   date created 	: 13 July 2018
   date modified	:--
   Author		: Raja shekar
 */

#include"headers.h"

#define PORT 8080

void calculatespeed( double , long );
/***********  launching of client process using the socket *******************/

void send_socket(long datasize)
{
	clock_t start , end;
	long Databytes=0 , count= datasize/1000;
printf("data = %ld  count = %ld \n", datasize , count);
	double timeconsumed =0 ;
	struct sockaddr_in address;
	int socketfd = 0;
	struct sockaddr_in serv_addr;
	char *hello = "Hello from client";
	char buffer[1000] = {0};
	if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return ;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{
		printf("\nInvalid address/ Address not supported \n");
		return ;
	}

	if (connect(socketfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return ;
	}
while(count--)
{
	start=clock();
	send(socketfd , hello , strlen(hello) , 0 );
//	printf("Hello message sent\n");
	end = clock();
	timeconsumed += (double)(end-start)/CLOCKS_PER_SEC;
	Databytes += strlen(hello);
}
	read( socketfd , buffer, 1000);
	printf("%s\n",buffer );
	calculatespeed( timeconsumed , Databytes );
	return ;
}


/***********  launching of server process using the socket *******************/

void receive_socket(long datasize)
{
	clock_t start , end;
	long Databytes=0 , count= datasize/1000;
printf("data = %ld  count = %ld \n", datasize , count);
	double timeconsumed =0 ;
	int server_fd, new_socket;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1000] = {0};
	char *hello = "Hello from server";

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}

while(count--)
{
	start=clock();
	read( new_socket , buffer, 1000);
	end=clock();
	timeconsumed += (double)(end-start)/CLOCKS_PER_SEC;
	Databytes += strlen(buffer);
	printf("%s\n",buffer );
}
	send(new_socket , hello , strlen(hello) , 0 );
	printf("Hello message sent\n");
	calculatespeed( timeconsumed , Databytes );
	return ;
}

