#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main()
{
//struct sockaddr_in cin,client_addr;
int sid;
char MAC[50];
char *string;
int size=50;
string=(char*)malloc(size);
char getip[50];
int i,count=0;
sid=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
if(sid==-1)
{
perror("Socket Error\n");
}
else
{
printf("\nSocket Created");
struct sockaddr_in addrport;
  addrport.sin_family=AF_INET;
  addrport.sin_port=htons(30000);
  addrport.sin_addr.s_addr=inet_addr("127.16.16.200");
  int status=bind(sid,(struct sockaddr*)&addrport,sizeof(addrport));
  if(status==-1)
  {
   printf("\nbinding unsuccessful!..program terminated!");
   return 0;
  }
  printf("\nbinded successfully..!");
  struct sockaddr_in client_addr;
  client_addr.sin_family=AF_INET;
  client_addr.sin_port=htons(30000);
  client_addr.sin_addr.s_addr=inet_addr("127.16.16.200");
  socklen_t  n=sizeof(client_addr);
char ip[50];
int count=recvfrom(sid,ip,(size_t)sizeof(ip),0,(struct sockaddr*)&client_addr,&n);
FILE *ptr;
ptr=fopen("DNS.txt","r");
if(ptr==NULL)
{
	perror("No such file found!");
}
else
{
	while(!feof(ptr))
	{
		int nof=getline(&string,&size,ptr);
		for(i=0;string[i]!=':';i++)
		{
			if(string[i]!=':')
			{
			getip[i]=string[i];
			count++;
			}
			else
				break;
		}
		if(strcmp(getip,ip)==0)
		{
			printf("Match found for %s !! Sending it to Client\n The IP is: ",getip);
			int k=0;
			for(i=i+2;string[i]!='\n';i++)
			{
				MAC[k]=string[i];
				k++;
			}
			puts(MAC);
			int snd=sendto(sid,MAC,sizeof(MAC),0,(struct sockaddr*)&client_addr,sizeof(client_addr));
			break;
		}
		else
		{
			memset(getip,'\0',sizeof(getip));
			if(feof(ptr))
			{
				printf("No Such DNS in Server\n");
				strcpy(MAC,"");
				int snd=sendto(sid,MAC,sizeof(MAC),0,(struct sockaddr*)&client_addr,sizeof(client_addr));
			}
		}
	}
}
}
}

