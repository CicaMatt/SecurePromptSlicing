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

int main(int argc, char *argv[]) {
    int sockfd, newsockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    char buffer[BUFFER_SIZE];
    FILE *fp;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR on binding");
    
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) 
         error("ERROR on accept");

    bzero(buffer,BUFFER_SIZE);
    int n = read(newsockfd, buffer, BUFFER_SIZE-1);
    if (n < 0) error("ERROR reading from socket");
    
    char *filename = "uploaded_file";
    fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Error opening file for writing\n");
        return 1;
    }

    while ((n = read(newsockfd, buffer, BUFFER_SIZE)) > 0) {
        fwrite(buffer, sizeof(char), n, fp);
    }
    fclose(fp);

    char response[] = "File received successfully";
    n = write(newsockfd,response,strlen(response));
    if (n < 0) error("ERROR writing to socket");

    close(newsockfd);
    close(sockfd);
    return 0; 
}