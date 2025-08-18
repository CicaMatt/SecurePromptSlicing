#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock session structure for demonstration purposes
typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

// Function to simulate retrieving data from a session
Session get_session_data() {
    Session session;
    session.username = "JohnDoe";
    session.email = "john.doe@example.com";
    session.ssn = "123-45-6789";
    return session;
}

void handle_info_request() {
    Session session = get_session_data();
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/plain\r\n");
    printf("\r\n");
    printf("Username: %s\n", session.username);
    printf("Email: %s\n", session.email);
    printf("SSN: %s\n", session.ssn);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int port = atoi(argv[1]);

    // Simple TCP server setup
    int sockfd, newsockfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("ERROR opening socket");
        return EXIT_FAILURE;
    }

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        close(sockfd);
        return EXIT_FAILURE;
    }

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0) {
            perror("ERROR on accept");
            continue;
        }

        char buffer[256];
        bzero(buffer, 256);
        read(newsockfd, buffer, 255);

        // Check for the /info GET request
        if (strncmp(buffer, "GET /info HTTP/1.1", 18) == 0) {
            handle_info_request();
        } else {
            printf("HTTP/1.1 404 Not Found\r\n");
            printf("Content-Type: text/plain\r\n");
            printf("\r\n");
            printf("Not Found\n");
        }

        close(newsockfd);
    }

    close(sockfd);
    return EXIT_SUCCESS;
}