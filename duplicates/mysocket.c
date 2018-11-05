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

void client_socket(long datasize)
{
	clock_t start , end;
	long Databytes=0 , count= datasize/100;
	printf("data = %ld  count = %ld \n", datasize , count);
	double timeconsumed =0 ;

	// structure used for internet socket addressing 
	int socketfd = 0;
	struct sockaddr_in serv_addr;

	char buffer[100] = ")*456789hello world this is raja sara JHgdjasg fj Jh sdj fb k ui JG FSDfhsdhfSHDFKSGFkgsDKFGDSJK FGS";;
	if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return ;
	}
	// To clear the structure data present in it
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
	//srand(getpid());
	while(count--)
	{
		//		buffer[0]=rand()%26 + 65;  // This can be used to ensure that data is copied every time
		//		printf("%s\n",buffer);
		start=clock();
		write( socketfd , buffer , sizeof(buffer) ) ;
		end = clock();
		timeconsumed += (double)(end-start)/CLOCKS_PER_SEC;
		Databytes += strlen(buffer);
	}
	calculatespeed( timeconsumed , Databytes );
	close(socketfd);
	return ;
}


/***********  launching of server process using the socket *******************/

void server_socket(long datasize)
{
	clock_t start , end;
	long Databytes=0 , count= datasize/100;
	printf("data = %ld  count = %ld \n", datasize , count);
	double timeconsumed =0 ;
	int server_fd, new_socketfd;

	//	int opt=1;

	struct sockaddr_in address;
	int addrlen = sizeof(address);
	char buffer[100] = {0};

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	/*
	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
	perror("setsockopt");
	exit(EXIT_FAILURE);
	}
	 */

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
		read( new_socketfd , buffer, 100 ) ;
		end=clock();
		//		printf("%s\n",buffer);
		timeconsumed += (double)(end-start)/CLOCKS_PER_SEC;
		Databytes += strlen(buffer);
	}
	calculatespeed( timeconsumed , Databytes );
	close(server_fd);
	close(new_socketfd);
	return ;
}

