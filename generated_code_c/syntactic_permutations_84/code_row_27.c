#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <yaml.h>

#define PORT 5000
#define YAML_SIZE 1024
#define MAX_REQUEST_LENGTH 65536

void printError(const char *message) {
    fprintf(stderr, "error: %s\n", message);
    exit(EXIT_FAILURE);
}

int main() {
    int sockfd;
    struct sockaddr_in serverAddr;
    
    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printError("socket creation failed");
    }
    
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);
    
    // Bind and listen on socket
    if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        printError("binding failed");
    }
    if (listen(sockfd, 3) < 0) {
        printError("listening failed");
    }
    
    // Accept a connection on socket
    int clientSocket;
    struct sockaddr_in clientAddr;
    uint addrLen = sizeof(clientAddr);
    if ((clientSocket = accept(sockfd, (struct sockaddr *)&clientAddr, &addrLen)) < 0) {
        printError("accept failed");
    }
    
    // Read request from client socket
    char request[MAX_REQUEST_LENGTH];
    int readLength;
    if ((readLength = recv(clientSocket, request, MAX_REQUEST_LENGTH - 1, 0)) < 0) {
        printError("recv failed");
    }
    
    // Check if payload parameter is present and parse as YAML
    char *payload = strstr(request, "payload=");
    if (payload == NULL) {
        const char *errorMessage = "missing payload parameter";
        send(clientSocket, errorMessage, strlen(errorMessage), 0);
        close(sockfd);
        return EXIT_FAILURE;
    }
    yaml_parser_t parser;
    if (!yaml_parser_initialize(&parser)) {
        printError("failed to initialize YAML parser");
    }
    yaml_parser_set_input_string(&parser, payload, strlen(payload));
    
    // Check if YAML type is Create and return error message
    yaml_event_t event;
    int done = 0;
    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            printError("error parsing YAML");
        }
        switch (event.type) {
        case YAML_MAPPING_START_EVENT:
            done = 1;
            break;
        case YAML_SCALAR_EVENT:
            if (!strcmp((char *)event.data.scalar.value, "type")) {
                if (yaml_parser_parse(&parser, &event)) {
                    const char *errorMessage = "invalid type parameter";
                    send(clientSocket, errorMessage, strlen(errorMessage), 0);
                    close(sockfd);
                    return EXIT_FAILURE;
                }
                if (strcmp((char *)event.data.scalar.value, "Create")) {
                    const char *errorMessage = "invalid type parameter";
                    send(clientSocket, errorMessage, strlen(errorMessage), 0);
                    close(sockfd);
                    return EXIT_FAILURE;
                }
            }
            break;
        default:
            break;
        }
    }
    
    // Clean up and return success message
    yaml_parser_delete(&parser);
    const char *successMessage = "OK";
    send(clientSocket, successMessage, strlen(successMessage), 0);
    close(sockfd);
    return EXIT_SUCCESS;
}