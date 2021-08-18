#include "head.h"

int latdegree,latmin,latsec;
int londegree,lonmin,lonsec;
extern int serv()
{
int sockfd;
	int len;
	struct sockaddr_in address;
	 int result;
unlink("sockfd");
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("192.168.43.252");
	address.sin_port=9640;
	len=sizeof(address);

	result=connect(sockfd,(struct sockaddr *)&address,len);

	if(result==-1){
	perror("oops!");
	exit(1);
	}
	

send(sockfd,&latdegree,sizeof(latdegree),0);
send(sockfd,&latmin,sizeof(latmin),0);
send(sockfd,&latsec,sizeof(latsec),0);
send(sockfd,&londegree,sizeof(londegree),0);
send(sockfd,&lonmin,sizeof(lonmin),0);
send(sockfd,&lonsec,sizeof(lonsec),0);
printf("Gps data sent successfully");
close(sockfd);
if(system("chromium-browser /home/sidd/Desktop/SimpleRTC-gh-pages/minivid2.html"))
printf("Html could not be opened");
exit(0);

}
