#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h> 
#include <sys/types.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <arpa/inet.h>
#define BUFFSIZE 1024 
#define QUEUE 64

int main(){
    int sockfd, newsockfd, portno; 
    char buffer[BUFFSIZE]; 
    struct sockaddr_in serv_addr, cli_addr; 
    socklen_t clilen;
    
    //Socket creation
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd < 0) { 
        perror("ERROR opening socket"); 
        exit(1); 
    } 
    
    bzero((char *) &serv_addr, sizeof(serv_addr)); 
    portno = 80; //Port Number
    
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_addr.s_addr = INADDR_ANY; 
    serv_addr.sin_port = htons(portno);
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) { 
        perror("ERROR on binding"); 
        exit(1); 
    } 
    
    //Listening to incoming connections
    listen(sockfd, QUEUE);
    clilen = sizeof(cli_addr);
    
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) { 
        perror("ERROR on accept"); 
        exit(1); 
    }
    bzero(buffer, BUFFSIZE);
    
    int n = read(newsockfd, buffer, BUFFSIZE); 
    if (n < 0) { 
        perror("ERROR reading from socket"); 
        exit(1); 
    }
    
    //Writing a response to the client
    char * message = "Hello from server"; 
    n = write(newsockfd, message, strlen(message)); 
    if (n < 0) { 
        perror("ERROR writing to socket"); 
        exit(1); 
    }
    
    return 0; 
}