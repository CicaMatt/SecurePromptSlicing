#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
 
#define PORT 5000
#define MAXPENDING 1
#define BUFFSIZE 80
 
int main(void) {
    int sockfd, newsockfd; // listen on sock_fd, new connection on new_fd
    struct sockaddr_in serverAddress, clientAddress;
    socklen_t cliLen = sizeof(clientAddress);
 
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("ERROR: Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("\nServer waiting for client...\n");
 
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);
 
    if (bind(sockfd, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        perror("ERROR: Socket binding failed");
        exit(EXIT_FAILURE);
    }
 
    if (listen(sockfd, MAXPENDING) < 0) {
        perror("ERROR: Socket listening failed");
        exit(EXIT_FAILURE);
    }
 
    while (1) {
        char buffer[BUFFSIZE];
        memset(&clientAddress, 0, sizeof(clientAddress));
        newsockfd = accept(sockfd, (struct sockaddr *) &clientAddress, &cliLen);
        if (newsockfd < 0) {
            perror("ERROR: Accept failed");
            exit(EXIT_FAILURE);
        }
        printf("\nClient connected...\n");
 
        char *payload = strstr(buffer, "payload=");
        if (!payload || !strstr(payload + 8, "\r\n")) {
            sprintf(buffer, "HTTP/1.0 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 23\r\n\r\nError: Missing payload parameter");
            send(newsockfd, buffer, strlen(buffer), 0);
        } else {
            char *yaml = payload + 8;
            if (!strncmp(yaml, "type=Create", 10)) {
                sprintf(buffer, "HTTP/1.0 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 23\r\n\r\nError: Unsupported type");
                send(newsockfd, buffer, strlen(buffer), 0);
            } else {
                sprintf(buffer, "HTTP/1.0 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 9\r\n\r\nSuccess");
                send(newsockfd, buffer, strlen(buffer), 0);
            }
        }
        close(newsockfd);
    }
}