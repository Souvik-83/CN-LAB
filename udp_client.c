#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main()
{
int cn,cs;
cn=socket(AF_INET,SOCK_DGRAM,0);
if (cn==-1)
{
printf("client socket connection failed");
return 0;
}
printf("Client socket created successfully\n");
struct sockaddr_in cadd;
cadd.sin_family=AF_INET; // memorize
cadd.sin_port=htons(5000);// memorize
cadd.sin_addr.s_addr=INADDR_ANY;// memorize
cs=bind(cn,(struct sockaddr*)&cadd,sizeof(cadd));// memorize
if(cs==-1)
{
printf("Client binding failed\n");
return 0;
}
printf("Connection successful from client side\n");

struct sockaddr_in toadd;
toadd.sin_family=AF_INET;
toadd.sin_port=htons(3000);
toadd.sin_addr.s_addr=INADDR_ANY;

char cstr[200];
printf("Enter the message to be sent : ");
scanf("%s",cstr);
int cbyte=sendto(cn,cstr,sizeof(cstr),0,(struct sockaddr*)&toadd,sizeof(toadd));

if(cbyte==-1)
{
printf("Message not sent");
exit(0);
}
printf("Message sent");

struct sockaddr_in receive;
receive.sin_family=AF_INET;
receive.sin_port=htons(3000);
receive.sin_addr.s_addr=INADDR_ANY;
char cctr[200];
int size2;
int c_resbyte=recvfrom(cn,cctr,200,0,(struct sockaddr*)&receive,&size2);
if (c_resbyte==-1)
{
printf("Message not received");
exit(0);
}
printf("Message received is successful\n");
printf("%d bytes received ",c_resbyte);
printf("%s",cctr);
return 0;
}