#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/unistd.h>
#include <sys/errno.h>

/*interprocess communication: client->server model
Client side
1. create the socket with the socket syscall
2.connect the socket to the address of the server using the connect system call
3.send and receive data ( read,write syscall)

Server side
1.Create the socket with the socket syscall
2.Bind the socket to an address using bind
3.Listen for connections with the listen syscall
4.Accept a connection with the syscall
5.Send and receive data */

int main(int argc, char *argv[])
{
	int sockfd,newsockfd,port,clilen,n; /*file descriptors andport on which the server accepts commnication, number of chars read/received*/
	char buffer[256];
	struct sockaddr_in server, client;
	if ( argc < 2 ) /*need to pass port on which the servers accepts connections*/
		fprintf(stderr, "No port provided");

	sockfd = socket( AF_INET, SOCK_STREAM, 0);
	printf("%d", sockfd);

	if(sockfd <0)
		error("Error opening socket");

	port = atoi(argv[1]);
	printf("%d", port);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = INADDR_ANY;/*don't care about ip of the machine , allow to receive packets destined to any of the available interfaces*/

	if ( bind(sockfd,(struct sockaddr*)&server, sizeof(server)) < 0)
		error("Socket not bound");

	listen(sockfd , 5);

	clilen = sizeof(client);

	newsockfd = accept(sockfd, (struct sockaddr*)&client, &clilen); /* accepting socket from client*/
	if(newsockfd <0)
		error("Not accepted");
	printf("Waiting for the client");
	n = read(newsockfd, buffer, 255);
	printf( " Message received from the client : %s" , buffer);
	n = write(newsockfd, " Received", 18);

return 0;
}