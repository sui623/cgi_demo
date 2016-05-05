#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
int main(int argc, char* argv[],char *envp[] )
{
	int sockfd = 0, n = 0;
	int len_unix; 
	char recvBuff[1024],sentBuff[1024];
	char format[20];
	struct sockaddr_un serv_addr; 

  	const char pth_unix[]   = "ZSUI_SOCKET";

	printf("Content-type: text/html\n\n");

	int length=atoi(getenv("CONTENT_LENGTH"));
   	//printf("length=%d\n", length);
   	
   	sprintf(format, "user_name=%%%dc", length); 
	scanf(format, sentBuff);

	
    	if((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    	{
        	printf("\n Error : Could not create socket \n");
        	return 1;
   	} 

    	memset(&serv_addr, '0', sizeof(serv_addr)); 

    	serv_addr.sun_family = AF_UNIX;
	strncpy(serv_addr.sun_path,pth_unix,sizeof serv_addr.sun_path-1)[sizeof serv_addr.sun_path-1] = 0;
	len_unix = SUN_LEN(&serv_addr);
	serv_addr.sun_path[0] = 0;	
 

    	if( connect(sockfd, (struct sockaddr *)&serv_addr, len_unix) < 0)
    	{
       		printf("\n Error : Connect Failed \n");
       		return 1;
    	}

	n=write(sockfd,sentBuff,sizeof(sentBuff));

	memset(recvBuff, '0',sizeof(recvBuff));
    	while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
    	{
        	recvBuff[n] = 0;
		
        	if(fputs(recvBuff, stdout) == EOF)
        	{
            		printf("\n Error : Fputs error\n");
        	}
    	} 

    	if(n < 0)
    	{
        	printf("\n Read error \n");
	} 
	
	return 0;

}
