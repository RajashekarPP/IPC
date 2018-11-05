/*
   File Name	 	: socket.c
   date created 	: 13 July 2018
   date modified	: changed the way in such a way that the client will be waiting till the server is connected or launched
Author		: Raja shekar
 */


#include"headers.h"

#define PORT 3450


/***********  launching of client process using the socket *******************/

void client_socket(long datasize)
{
	clock_t start , end;
	long Databytes=0 , count= datasize/SIZE;
	printf("data = %ld  count = %ld \n", datasize , count);
	double timeconsumed =0 ;

	// structure used for internet socket addressing 
	int socketfd = 0;
	struct sockaddr_in servaddr;

	char buffer[SIZE]="*456789hello world this is raj FSDfhsdhfSHDFKSGFkgsDKFGDSJK FGS";;
	if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return ;
	}

	// To clear the structure data present in it
	memset(&servaddr, '0', sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr)<=0) 
	{
		printf("\nInvalid address/ Address not supported \n");
		return ;
	}


// waiting for the server to be initialized or connected
	while (connect(socketfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1);

	while(count--)
	{
		start=clock();
		write( socketfd , buffer , SIZE ) ;
		end = clock();
		timeconsumed += (double)(end-start)/CLOCKS_PER_SEC;
		Databytes += SIZE;
	}
	calculatespeed( timeconsumed , Databytes , "socket");
	close(socketfd);
	return ;
}







/***********  launching of server process using the socket *******************/

void server_socket(long datasize)
{
	clock_t start , end;
	long Databytes=0 , count= datasize/SIZE;
	printf("data = %ld  count = %ld \n", datasize , count);
	double timeconsumed =0 ;
	int server_fd, new_socketfd;

	struct sockaddr_in address;
	int addrlen = sizeof(address);
	char buffer[SIZE];

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY; // receive from any client or system
	address.sin_port = htons( PORT );

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	puts("binding success ");

	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	puts("Listened to one of the client is sucess");

	if ((new_socketfd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}

	puts("accepting data from one of the client connected ");
	while(count--)
	{
		start=clock();
		read( new_socketfd , buffer, SIZE ) ;
		end=clock();
		timeconsumed += (double)(end-start)/CLOCKS_PER_SEC;
		Databytes += SIZE;
	}
	calculatespeed( timeconsumed , Databytes , "socket" );
	close(server_fd);
	close(new_socketfd);
	return ;
}

