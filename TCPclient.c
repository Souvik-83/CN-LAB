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


//connect API
struct sockaddr_in addr;
addr.sin_family=AF_INET; /* address family: AF_INET */
addr.sin_port=8040;   /* port in network byte order */
addr.sin_addr.s_addr=INADDR_ANY;  
int cn=connect(sock,(const struct sockaddr*)&addr,sizeof(addr));
if(cn==-1)
{
printf("Error in connection");
exit(1);
}


//recv API
FILE *f=fopen("res.txt","w");
while(1)
{
char recv_buff[100];
int rv=recv(sock,recv_buff,sizeof(recv_buff),0);
if(rv==-1)
{
printf("Error when receiving");
exit(1);
}
int size=fwrite(recv_buff,5,100,f);
if(size<100)
break;
}






//close API
int c=close(sock);
if(c==-1)
{
printf("Error in closing file");
exit(1);
}
return 0;
}
