#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SOCKET "SocketUNIX"


int main(void)
{
struct sockaddr_un client;
char buffer[100];
int cli, rc;
cli = socket( AF_UNIX, SOCK_STREAM, 0);
memset(&client, 0, sizeof( client));
client.sun_family = AF_UNIX;
strcpy(client.sun_path,SOCKET);

if(connect(cli, (struct sockaddr*)&client, sizeof(client)) == -1)
	printf("error connect");

while (rc = read(STDIN_FILENO,buffer,sizeof(buffer)))
{
 if(rc != 0)
 	write(cli, buffer,sizeof(buffer));

}
close (cli);
return 0;
}