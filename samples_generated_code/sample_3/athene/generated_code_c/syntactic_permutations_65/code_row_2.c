#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>

#define PORT "8080"
#define BUFFER_SIZE 1024
#define FILE_PATH "./uploaded.pdf"

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int sockfd, numbytes;
    char buf[BUFFER_SIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo("127.0.0.1", PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            continue;
        }

        break;
    }

    if (p == NULL) {
        error("Failed to connect");
    }

    freeaddrinfo(servinfo);

    char *request = "POST /upload HTTP/1.1\r\n"
                    "Host: 127.0.0.1:8080\r\n"
                    "Content-Type: application/x-www-form-urlencoded\r\n"
                    "Content-Length: 0\r\n\r\n";

    if (send(sockfd, request, strlen(request), 0) == -1) {
        error("Failed to send request");
    }

    int file = open(FILE_PATH, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    if (file == -1) {
        error("Failed to create file");
    }

    while ((numbytes = recv(sockfd, buf, BUFFER_SIZE - 1, 0)) > 0) {
        if (write(file, buf, numbytes) != numbytes) {
            close(file);
            error("Failed to write to file");
        }
    }

    if (numbytes == -1) {
        close(file);
        error("Failed to receive data");
    }

    close(file);
    close(sockfd);

    return 0;
}