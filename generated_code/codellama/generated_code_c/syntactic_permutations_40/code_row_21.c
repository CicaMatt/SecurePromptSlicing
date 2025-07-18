++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <time.h>

#define PORT "3000"
#define BACKLOG 100
#define MAXDATASIZE 1024

int main(void) {
    // create and initialize socket
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 
    char sendBuff[MAXDATASIZE];
    time_t ticks;
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(PORT)); 
    
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
    
    listen(listenfd, BACKLOG);
    
    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

    // read and process client request
    char recvBuff[MAXDATASIZE];
    int numbytes = 0;
    
    while ((numbytes = recv(connfd, recvBuff, MAXDATASIZE-1, 0)) > 0) {
        recvBuff[numbytes] = '\0';
        
        // process request and create response
        char sendMessage[] = "<html><body>";
        
        int len = strlen(sendMessage);
        snprintf(sendBuff, sizeof(sendBuff), "%s", sendMessage); 
        
        send(connfd, sendBuff, len, 0);
    }
    
    if (numbytes == -1) {
        perror("recv");
        exit(1);
    }

    // close socket and connection
    close(listenfd);
    close(connfd);
    
    return 0;
}