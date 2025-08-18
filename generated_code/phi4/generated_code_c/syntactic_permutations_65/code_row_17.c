#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int sockfd, newsockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    // Initialize socket structure
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    // Bind the host address
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR on binding");

    // Start listening for the clients
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0)
            error("ERROR on accept");

        FILE *file;
        char buffer[1024];
        int n;

        // Read file name
        bzero(buffer, 1024);
        n = read(newsockfd, buffer, 1023);
        if (n < 0) error("ERROR reading from socket");
        printf("File Name: %s\n", buffer);

        char filePath[256];
        snprintf(filePath, sizeof(filePath), "./uploads/%s", buffer);

        // Create directory if it doesn't exist
        system("mkdir -p uploads");

        // Open file to write
        file = fopen(filePath, "wb");
        if (!file) {
            error("ERROR opening file for writing");
        }

        // Read data from socket and write to the file
        while ((n = read(newsockfd, buffer, 1023)) > 0) {
            fwrite(buffer, sizeof(char), n, file);
        }
        fclose(file);

        if (n < 0) error("ERROR reading from socket");

        close(newsockfd);
    }

    close(sockfd);
    return 0;
}