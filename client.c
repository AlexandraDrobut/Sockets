#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/unistd.h>
#include <sys/errno.h>
#include <netdb.h>
#include <strings.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int sockfd, port, n;
	struct sockaddr_in server;
	struct hostent *serverh;
	char buffer[256];

	port = atoi(argv[2]);

	serverh = gethostbyname(argv[1]);

	sockfd = socket( AF_INET,SOCK_STREAM, 0 );
	bzero((char*)&server,sizeof(server));

	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	bcopy((char*)serverh->h_addr,(char*)&server.sin_addr.s_addr,serverh->h_length);
	if(connect(sockfd,(struct sockaddr*)&server,sizeof(server)) < 0 )
		printf("Error Connecting");

	printf("Connecting");

	bzero(buffer,256);
	fgets(buffer, 256, stdin);
	n = write(sockfd, buffer,strlen(buffer));
	if(n<0)
		printf("Failed writing to socket");
	bzero(buffer,256);
	n = read(sockfd, buffer, 255);
	if(n<0)
		printf("Error reading from socket");
	return 0;
}