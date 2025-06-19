// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Defines
#define REQUEST_LENGTH 1024
#define RESPONSE_LENGTH 1024
#define REDIRECT_URL_LENGTH 512

// Function prototypes
void redirect(int socket, char* target);
char* getTarget(char* request);
void closeSocket(int socket);

// Main function
int main() {
    // Create the server socket
    int serverSocket;
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Error creating the server socket");
        exit(EXIT_FAILURE);
    }

    // Set up the server address
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the address and port
    if (bind(serverSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0) {
        perror("Error binding the server socket");
        exit(EXIT_FAILURE);
    }

    // Listen on the socket for incoming connections
    if (listen(serverSocket, 3) < 0) {
        perror("Error listening on the server socket");
        exit(EXIT_FAILURE);
    }

    printf("Server started and waiting for connections...\n");

    // Accept incoming connections
    while (1) {
        int clientSocket;
        struct sockaddr_in clientAddress;
        int addressLength = sizeof(clientAddress);

        if ((clientSocket = accept(serverSocket, (struct sockaddr*) &clientAddress, &addressLength)) < 0) {
            perror("Error accepting the client connection");
            continue;
        }

        // Get the request from the client
        char request[REQUEST_LENGTH];
        read(clientSocket, request, REQUEST_LENGTH);

        // Get the target from the request
        char* target = getTarget(request);

        // Check if the target matches a regular expression
        regex_t regex;
        int status = regcomp(&regex, "http://[^/]+.example.com/?.*", REG_EXTENDED | REG_NOSUB);
        char* redirectUrl = (status == 0) ? target : "/";

        // Redirect the client to the target or the root page
        redirect(clientSocket, redirectUrl);

        // Close the client socket
        closeSocket(clientSocket);
    }

    return 0;
}

// Function definitions
void redirect(int socket, char* target) {
    // Compose the HTTP response message
    char* response = "HTTP/1.1 302 Found\r\nLocation: ";
    strcat(response, target);
    strcat(response, "\r\nConnection: close\r\n");
    printf("Redirecting to %s...", target);

    // Send the response message to the client
    write(socket, response, RESPONSE_LENGTH);
}

char* getTarget(char* request) {
    char* target = strstr(request, "GET /?target=");
    if (target != NULL) {
        target += 13;
    } else {
        target = "/";
    }
    return target;
}

void closeSocket(int socket) {
    printf("Connection closed.\n");
    close(socket);
}