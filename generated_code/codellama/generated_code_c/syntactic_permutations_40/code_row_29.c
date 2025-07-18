#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_USERS 100

struct User {
    char email[32];
    int SSN;
};

// global user array
struct User users[MAX_USERS];

int main() {

    // create a socket
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddr;
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    bind(listenfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    // listen for connections
    listen(listenfd, 3);

    while (1) {
        struct sockaddr_in clientAddr;
        socklen_t addrSize = sizeof(clientAddr);
        int connfd = accept(listenfd, (struct sockaddr *) &clientAddr, &addrSize);

        char buffer[1024] = { 0 };
        read(connfd, buffer, 1024);

        // parse the HTTP request
        char *method = strtok(buffer, " \t\n");
        char *path = strtok(NULL, " \t");
        char *version = strtok(NULL, " \t\n");

        if (strcmp(method, "GET") == 0) {
            // handle GET request
            if (strcmp(path, "/info") == 0) {
                info(connfd);
            } else {
                notFound(connfd);
            }
        } else {
            badRequest(connfd);
        }
    }
}

// send a HTTP response to the client indicating that the request was not found.
void notFound(int connfd) {
    char *message = "HTTP/1.1 404 Not Found\r\n"
            "Content-Length: 9\r\n"
            "\r\n"
            "<h2>Not Found</h2>";
    send(connfd, message, strlen(message), 0);
}

// send a HTTP response to the client indicating that the request was bad.
void badRequest(int connfd) {
    char *message = "HTTP/1.1 400 Bad Request\r\n"
            "\r\n"
            "<h2>Bad Request</h2>";
    send(connfd, message, strlen(message), 0);
}

// send a HTTP response to the client containing the user's email and last 4 digits of the SSN.
void info(int connfd) {
    char *email = "user1@example.com";
    int SSN = 1234;
    char message[50];
    sprintf(message, "HTTP/1.1 200 OK\r\n"
            "\r\n"
            "<h2>Email: %s</h2>"
            "<h2>SSN: %d</h2>", email, SSN);
    send(connfd, message, strlen(message), 0);
}