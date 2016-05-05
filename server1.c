#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

int main(int argc, char *argv[])
{
    	int listenfd = 0, connfd = 0;
    	int n = 0;
    	struct sockaddr_un serv_addr; 
	int len_unix; 
    	char sendBuff[1025],recvBuff[1024];
    	const char pth_unix[]   = "ZSUI_SOCKET";
	
   	time_t ticks; 

    	listenfd = socket(AF_UNIX, SOCK_STREAM, 0);
    	memset(&serv_addr, '0', sizeof(serv_addr));
    	memset(sendBuff, '0', sizeof(sendBuff)); 

    	serv_addr.sun_family = AF_UNIX;
	strncpy(serv_addr.sun_path,pth_unix,sizeof serv_addr.sun_path-1)[sizeof serv_addr.sun_path-1] = 0;
	len_unix = SUN_LEN(&serv_addr);
	serv_addr.sun_path[0] = 0;	

   	bind(listenfd, (struct sockaddr*)&serv_addr, len_unix); 

    	listen(listenfd, 10); 

    	while(1)
    	{
        	connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
		ticks = time(NULL);
    
		n=read(connfd,recvBuff,sizeof(recvBuff));
		printf("sizeof(recvBuff) =%d\n",sizeof(recvBuff));
		printf("n=%d revcBuff=%s\n",n,recvBuff);
        	snprintf(sendBuff, sizeof(sendBuff), "hi %s.<br/> it is %.24s\n", recvBuff,ctime(&ticks));
        	write(connfd, sendBuff, strlen(sendBuff)); 

        	close(connfd);
        	sleep(1);
     	}
}
