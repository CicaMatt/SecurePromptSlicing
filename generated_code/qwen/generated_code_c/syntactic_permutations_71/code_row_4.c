#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serv_addr, cli_addr;
    FILE *fp;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = PORT;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) 
        error("ERROR on binding");

    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
    if (newsockfd < 0) 
         error("ERROR on accept");

    bzero(buffer,BUFFER_SIZE);
    int n = read(newsockfd,buffer,BUFFER_SIZE-1);
    if (n < 0) error("ERROR reading from socket");
    
    char *filename = "uploaded_file";
    fp = fopen(filename, "wb");
    if(fp == NULL) {
        perror("Error opening file for writing");
        exit(1);
    }

    while((n = read(newsockfd, buffer, BUFFER_SIZE)) > 0) {
        fwrite(buffer, sizeof(char), n, fp);
    }
    
    fclose(fp);

    close(newsockfd);
    close(sockfd);

    return 0; 
}