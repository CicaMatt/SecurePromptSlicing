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

int main(int argc, char *argv[]) {
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    FILE *file;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = PORT;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0)
            error("ERROR on accept");

        char buffer[256];
        bzero(buffer, 256);
        int n = read(newsockfd, buffer, 255);
        if (n < 0) error("ERROR reading from socket");
        
        char filename[100];
        sscanf(buffer, "UPLOAD %s", filename);

        file = fopen(filename, "wb");
        if (!file)
            error("ERROR opening file");

        while ((n = read(newsockfd, buffer, 255)) > 0) {
            fwrite(buffer, sizeof(char), n, file);
        }

        fclose(file);
        close(newsockfd);
    }

    close(sockfd);
    return 0;
}


This is a simple server-side C program that listens for connections and allows clients to upload files. The client must send the filename prefixed with "UPLOAD" followed by the actual file data over the socket.



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in serv_addr;
    FILE *file;

    if (argc != 3) {
        fprintf(stderr, "usage %s hostname filename\n", argv[0]);
        exit(0);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &serv_addr.sin_addr.s_addr);
    serv_addr.sin_port = htons(PORT);

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    char filename[100] = "UPLOAD ";
    strcat(filename, argv[2]);

    write(sockfd, filename, strlen(filename));

    file = fopen(argv[2], "rb");
    if (!file) {
        perror("File open failed");
        exit(1);
    }

    char buffer[256];
    while (fread(buffer, sizeof(char), 255, file) > 0) {
        write(sockfd, buffer, strlen(buffer));
    }
    
    fclose(file);
    close(sockfd);

    return 0;
}
