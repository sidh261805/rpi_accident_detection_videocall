//CLIENT PROGRAM
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
char recv_buff[2048];
int main(int argc,char*argv[])
{
int sockfd;
int len;
struct sockaddr_in addr;
int result;
sockfd=socket(AF_INET,SOCK_STREAM,0);
addr.sin_family=AF_INET;
addr.sin_addr.s_addr=inet_addr(argv[1]);
addr.sin_port=atoi(argv[2]);
len=sizeof(addr);
result=connect(sockfd,(struct sockaddr *)&addr,len);
if(result==-1)
{
perror("OOps unable to connect");
exit(1);
}
while(1)
{
int len_rd;
FILE *fd;
fd=fopen("/home/desd/Desktop/sample2.txt","a");
//len_rd=fread(&data1,1,sizeof(data1),fd);
len_rd=recv(sockfd,recv_buff,2048,0);
fwrite(recv_buff,1,strlen(recv_buff),fd);

printf("Char from server:\t%d\n",len_rd);
close(sockfd);
exit(0);
}
return 0;
}


