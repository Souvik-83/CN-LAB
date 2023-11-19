#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main()
{
int sn,bs;
char sstr[200];
sn=socket(AF_INET,SOCK_DGRAM,0);
if(sn==-1)
{
printf("Server socket connection failed");
return 0;
}
printf("Server socket created successful\n");

struct sockaddr_in sadd;
sadd.sin_family=AF_INET;
sadd.sin_port=htons(3000);
sadd.sin_addr.s_addr=INADDR_ANY;
bs=bind(sn,(struct sockaddr*)&sadd,sizeof(sadd));
if(bs==-1)
{
printf("Server binding failed\n");
return 0;
}
printf("Connection successful from server side\n");

struct sockaddr_in fradd;
fradd.sin_family=AF_INET;
fradd.sin_port=htons(5002);
fradd.sin_addr.s_addr=INADDR_ANY;

int size;
int sbyte=recvfrom(sn,sstr,200,0,(struct sockaddr*)&fradd,&size);
if (sbyte==-1)
{
printf("Message not received");
exit(0);
}
printf("Message received is successful\n");
printf("%d bytes received ",sbyte);
printf("%s",sstr);

char reply[300];
struct sockaddr_in response;
response.sin_family=AF_INET;
response.sin_port=htons(5000);
response.sin_addr.s_addr=INADDR_ANY;
if(sbyte>0)
{
printf("Enter your reply");
scanf("%s",reply);
int srbyte=sendto(sn,reply,sizeof(reply),0,(struct sockaddr*)&response,sizeof(response));
if (srbyte==-1)
{
printf("Message not sent");
exit(0);
}
printf("Message sent");
}
return 0;
}