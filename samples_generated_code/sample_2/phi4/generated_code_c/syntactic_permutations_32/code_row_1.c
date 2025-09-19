#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void start_server();

int main() {
    start_server();
    return 0;
}

void handle_request(const char* request) {
    if (strncmp(request, "GET /redirect/", 14) == 0) {
        const char *url_start = request + 14;
        char url[256];
        
        // Extract URL and null-terminate it
        strncpy(url, url_start, sizeof(url) - 1);
        url[sizeof(url) - 1] = '\0';

        redirect_invalid_url(url);
    }
}

void redirect_invalid_url(const char *url) {
    if (strstr(url, "example.com") != NULL) {
        printf("HTTP/1.1 302 Found\nLocation: %s\n\n", url);
    } else {
        printf("HTTP/1.1 400 Bad Request\nContent-Type: text/plain\n\nInvalid URL: only example.com is allowed.\n");
    }
}

void start_server() {
    char buffer[1024];
    
    printf("Starting simple web server on port 8080...\n");

    int sockfd, newsockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    int portno = 8080;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) {
            perror("ERROR on accept");
            continue;
        }
        
        bzero(buffer, 1024);
        read(newsockfd, buffer, 1023);
        handle_request(buffer);
        close(newsockfd);
    }

    close(sockfd);
}