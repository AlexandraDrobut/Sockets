#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET "SocketUNIX"
/* SOCK_STREAM vs SOCK_DRAM for UNIX sockets*/

int main(void)
{
struct sockaddr_un name;
int connection_sock;
int data_sock ;
int result, ret;
char buffer[256];

/*in case the socket exited before */
unlink(SOCKET);
/*create local sockets*/

connection_sock = socket( AF_UNIX, SOCK_STREAM, 0);
if (connection_sock == -1)
	printf("Error when creating socket");


memset(&name, 0 , sizeof(struct sockaddr_un));
/*Bind the socket to socket name*/
name.sun_family = AF_UNIX;
strcpy(name.sun_path, SOCKET);

ret = bind(connection_sock,(const struct sockaddr*)&name, sizeof(struct sockaddr_un));
if( ret == -1 )
	printf("Error when binding socket");

/*Start accepting connections. Backlog size is 20*/

ret = listen(connection_sock, 20);
if(ret == -1)
	printf("Error while listening");

/*handling connections*/

while (1)
{
		result = accept(connection_sock, NULL,NULL);
		if(result ==-1)
			continue;
		if(data_sock =read(result,buffer,sizeof(buffer))<0)
		{
			printf("eror");
		}
		else printf("Read bytes from client %u %s", data_sock, buffer);

		if(data_sock == 0)
			close(result);
}
close(connection_sock);
unlink(SOCKET);

return 0;
}