#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFSIZE 1024

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int sockfd, newsockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    char buffer[BUFSIZE];
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

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    while(1) {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0)
            error("ERROR on accept");

        bzero(buffer, BUFSIZE);
        int n = read(newsockfd, buffer, BUFSIZE-1);
        if (n < 0) error("ERROR reading from socket");

        char *filename = "uploaded_file";
        fp = fopen(filename, "wb");
        if(fp == NULL) {
            perror("ERROR opening file");
            exit(1);
        }

        while((n = read(newsockfd, buffer, BUFSIZE)) > 0) {
            fwrite(buffer, sizeof(char), n, fp);
        }
        fclose(fp);

        char *response = "File uploaded successfully!";
        write(newsockfd, response, strlen(response));

        close(newsockfd);
    }

    close(sockfd);
    return 0;
}