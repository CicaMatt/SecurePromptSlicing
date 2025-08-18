#include <stdio.h>
#include <string.h>

#define PORT 8080

// Sample user data
typedef struct {
    char username[50];
    char email[100];
    char ssn[12];
} User;

User getUserInfo() {
    User user = {"john_doe", "john.doe@example.com", "123-45-6789"};
    return user;
}

void handle_request(const char *request) {
    if (strcmp(request, "/info") == 0) {
        User user = getUserInfo();
        
        printf("HTTP/1.1 200 OK\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n"); // End of headers
        printf("Username: %s\n", user.username);
        printf("Email: %s\n", user.email);
        printf("SSN: %s\n", user.ssn);
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n"); // End of headers
        printf("Not Found\n");
    }
}

int main() {
    char buffer[1024];
    
    printf("Starting server on port %d...\n", PORT);
    int sockfd, newsockfd;
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        return 1;
    }

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        return 1;
    }

    listen(sockfd, 5);
    int clilen = sizeof(cli_addr);

    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
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
    return 0;
}