#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{

	// my ip address 10.3.10.197
	
	
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		printf("Error in creating socket");
		exit(0);
	}

	struct sockaddr_in bind_sock;
	bind_sock.sin_port = htons(8000);
	bind_sock.sin_family = AF_INET;
	

	int convert= inet_aton("10.3.10.197", &bind_sock.sin_addr);
	if(convert == -1)
	{
		printf("Error in conversion");
		exit(0);
	}
	

	int bind_ret = bind(sockfd, (const struct sockaddr *)&bind_sock, sizeof(bind_sock));
	if(bind_ret == -1)
	{
		printf("Error in bind socket");
		exit(0);
	}

	int listen_ret = listen(sockfd, 5);
	if(listen_ret == -1)
	{
		printf("Error in listen");
		exit(0);
	}
	
	
	while(1)
	{
	printf("Waiting for message ");
	struct sockaddr_in accept_sock;
	int accept_sock_size = sizeof(accept_sock);
	int accept_fd = accept(sockfd, (struct sockaddr *)&accept_sock, &accept_sock_size);
	if(accept_fd == -1)
	{
		printf("Error in accept");
		exit(0);
	}
	
	
	printf("IP address of the connected clint is: %s\n", inet_ntoa(accept_sock.sin_addr));
    printf("The port no is: %d\n", (int) ntohs(accept_sock.sin_port));

	/*printf("%d.%d.%d.%d\n",int(client.sin_addr.s_addr&0xFF),int((client.sin_addr.s_addr&0xFF00)>>8),int((client.sin_addr.s_addr&0xFF0000)>>16),int((client.sin_addr.s_addr&0xFF000000)>>24));
*/

	FILE * ptr;
	ptr=fopen("file1.txt","r");
	
	int eof_ret=feof(ptr);
	if(eof_ret==0)
	{
		printf("End of file ");
		exit(1);
	}
	
	while(eof_ret!=0)
	{
	
	char recv_buf[100];
	recv(accept_fd, recv_buf, sizeof(recv_buf), 0);
	//printf("message: %s\n", recv_buf);
	
	//read from the file
	
	int sys_ret =system(recv_buf);
	if(sys_ret==-1)
	{
		printf("error in sysyem api");
		exit(0);
	}

	char str[20];
	int file_ret= fread(str,1,20,ptr);
	if(file_ret==-1)
	{
		printf("\nError in file api");
		exit(0);
	}
	
	eof_ret=feof(ptr);
	if(eof_ret==0)
	{
		printf("End of file ");
		break;
	}
	//file api end 
	
	
	//printf("Enter message: ");
	send(accept_fd,str, strlen(str), 0);
	
	}
	
	close(accept_fd);
	
	}


	close(sockfd);


}
