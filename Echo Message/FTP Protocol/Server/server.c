#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main()
{
struct sockaddr_in cin,client_addr;
int sid;
char buffer[30];
char newstr[30];
sid=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
if(sid==-1)
{
perror("Socket Error\n");
}
else
{
printf("\nSocket Created");
cin.sin_family=AF_INET;
cin.sin_port=htons(30173);
cin.sin_addr.s_addr=htonl(INADDR_ANY);
if(bind(sid,(struct sockaddr*)&cin,sizeof(cin))!=-1);
{
printf("\nSocket Binded");
if(listen(sid,0)!=-1)
{
printf("\nIn Listening state....\n");
socklen_t n=sizeof(client_addr);
int nsid=accept(sid,(struct sockaddr*)&client_addr,&n);
if(nsid!=-1)
{
char filename[50];
int count=recv(nsid,filename,sizeof(filename),0);
FILE *ptr;
ptr=fopen(filename,"r");
if(ptr==NULL)
{
	perror("No such file found!");
}
else
{
	int c1=0;
	char contents;
	while((contents=fgetc(ptr))!=EOF)
	{
	c1++;
	}
	char newarr[c1];
	rewind(ptr);
	char string[20];
	snprintf(string,sizeof(string),"%d",c1);
	puts(string);
	int c4=send(nsid,string,sizeof(string),0);
	fgets(newarr,sizeof(newarr),ptr);
	int c3=send(nsid,newarr,sizeof(newarr),0);
	printf("\nFile sent to Client");
}
}
}
}
}
}
