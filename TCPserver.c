#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 
#include <string.h>
#include <unistd.h>

int main(){
//socket API
int sock=socket(AF_INET,SOCK_STREAM,0);
if(sock==-1)
{
printf("File couldn't be created...");
exit(1);
}

//bind API
struct sockaddr_in recv_soc;
recv_soc.sin_family=AF_INET; /* address family: AF_INET */
recv_soc.sin_port=5000;   /* port in network byte order */
recv_soc.sin_addr.s_addr=INADDR_ANY;     /* address in network byte order */

int r=bind(sock,(const struct sockaddr*)&recv_soc,sizeof(recv_soc));
if(r==-1)
{
printf("Error in bind...");
exit(1);
}
int l=listen(sock,5);
if(l==-1)
{
printf("Error in listening");
exit(1);
}
//accept API
struct  sockaddr_in sock_data;
int len=sizeof(sock_data);
int data_fd=accept(sock,(struct sockaddr*)&sock_data,&len);
if(data_fd==-1)
{
printf("Socket not accepted");
exit(1);
}
int sys=system("ls>res.txt");
if(sys==0)
printf("shell not available");

FILE* f=fopen("res.txt","r");

while(feof(f))
{char str[100];
int size=fread(str,5,100,f);
int l=strlen(str);
int s=send(sock,str,l,0);
}

int c=close(sock);
if(c==-1)
{
printf("Error in closing file");
exit(1);
}
return 0;
}
