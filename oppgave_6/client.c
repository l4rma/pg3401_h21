#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h> // fix sockaddr_in
#include <unistd.h> // fix read()

int main(int argc, char *argv[])
{
	struct sockaddr_in saAddr = {0};//Connect

	int sockFd, iPort = atoi("80");
	char *msg;
	char *bufPtr;
	char buffer[512];
	int readValue = 0;

	sockFd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockFd < 0){
		printf("socket failed with %i\n", errno);
	}

	saAddr.sin_family = AF_INET;
	saAddr.sin_port = htons(iPort);
	saAddr.sin_addr.s_addr = htonl(0x4D6FF04B);//(0x8EFA4A8E); // google 

	printf("Connecting to '0x%x'.. ", saAddr.sin_addr.s_addr);
	if(connect(sockFd, (struct sockaddr *)&saAddr, sizeof(saAddr)) < 0){
		printf("connect failed with %i\n\n", errno);
	}
	else
	{
		printf("Connected!\n\n");
	}

	/* Communication */

	// Send
	msg = "GET /pg3401/test.html HTTP/1.1\r\n"
		"Host: www.eastwillsecurity.com\r\n"
		//"Accept: text/html,application/xhtml+xml,application/xml;\r\n"
		"\r\n";
	send(sockFd, msg, strlen(msg), 0);
	printf("Sent from client:\n%s\n", msg);	

	// Read
	memset(buffer, 0, 512);
	readValue = read(sockFd, buffer, 512 -1);
	if(readValue < 0)
	{
		printf("read failed with %i\n", errno);
	}
	else
	{
		// skip headers and read out the body
		printf("Response body:\n");
		bufPtr = strstr(buffer, "\r\n\r\n");
		bufPtr+=4;
		printf("%s\n", bufPtr);
	}

	close(sockFd); sockFd = -1;
}
