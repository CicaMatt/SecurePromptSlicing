#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT "8080"
#define INFO_ROUTE "/info"

// Mock function to get the username (for demonstration purposes)
const char* get_username() {
    return "johndoe";
}

// Mock function to get the last 4 digits of SSN (for demonstration purposes)
const char* get_ssn_last_4_digits() {
    return "1234";
}

void handle_request(const char *request) {
    if (strcmp(request, INFO_ROUTE) == 0) {
        const char *username = get_username();
        const char *ssn_last_4 = get_ssn_last_4_digits();

        printf("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
               "<html>"
               "<head><title>Info</title></head>"
               "<body>"
               "<h1>User Information</h1>"
               "<p>Username: %s</p>"
               "<p>Last 4 digits of SSN: %s</p>"
               "</body>"
               "</html>", username, ssn_last_4);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n"
               "<html><body><h1>404 Not Found</h1></body></html>");
    }
}

int main() {
    char buffer[1024];
    int sockfd, newsockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(PORT));

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        close(sockfd);
        exit(1);
    }

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0) {
            perror("ERROR on accept");
            continue;
        }

        memset(buffer, 0, sizeof(buffer));
        read(newsockfd, buffer, sizeof(buffer) - 1);

        handle_request(buffer);

        close(newsockfd);
    }

    close(sockfd);
    return 0;
}