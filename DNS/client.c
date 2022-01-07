#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
int main()
{
//struct sockaddr_in cin,server_addr;
int cid;
char echo[30];
char ch;
//char buffer[30];
int len=0;
int i=0;
cid=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
if(cid==-1)
{
perror("Socket Error\n");
}
else
{
printf("Socket Created\n");
struct sockaddr_in addrport;
  addrport.sin_family=AF_INET;
  addrport.sin_port=htons(30001);
  addrport.sin_addr.s_addr=inet_addr("127.0.0.1");
  int status=bind(cid,(struct sockaddr*)&addrport,sizeof(addrport));char filename[50];
	if(status==-1)
  {
   printf("binding unsuccessful!..program terminated!\n");
   return 0;
  }
  printf("binded successfully..\n!");
  struct sockaddr_in client_addr;
  client_addr.sin_family=AF_INET;
  client_addr.sin_port=htons(30000);
  client_addr.sin_addr.s_addr=inet_addr("127.16.16.200");
printf("Connected\n");
printf("Enter the Domain Name to locate IP in server:");
gets(filename);
char s1[50];

int count=sendto(cid,filename,(size_t)sizeof(filename),0,(struct sockaddr*)&client_addr,sizeof(client_addr));
socklen_t n=sizeof(client_addr);
int c0=recvfrom(cid,s1,(size_t)sizeof(s1),0,(struct sockaddr*)&client_addr,&n);
if(strcmp(s1,"")!=0)
{
printf("\nThe IP is : %s \n",s1);
}
else
{
	printf("No such DNS is found in server...\n");
}
//}
}
}

