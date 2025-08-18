#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024

float getPrice(const char *productCode) {
    if (strcmp(productCode, "A123") == 0) return 9.99;
    if (strcmp(productCode, "B456") == 0) return 14.99;
    if (strcmp(productCode, "C789") == 0) return 7.99;
    return -1.0; // Invalid product code
}

void handleClient(int clientSocket) {
    char buffer[BUFFER_SIZE];
    int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        const char *requestMethod = "GET /price?";
        if (strncmp(buffer, requestMethod, strlen(requestMethod)) == 0) {
            const char *start = strstr(buffer, "?code=") + 6;
            const char *end = strchr(start, ' ');
            int len = end - start;
            char productCode[len + 1];
            strncpy(productCode, start, len);
            productCode[len] = '\0';
            float price = getPrice(productCode);

            if (price != -1.0) {
                const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
                send(clientSocket, response, strlen(response), 0);
                char priceStr[32];
                sprintf(priceStr, "%.2f", price);
                send(clientSocket, priceStr, strlen(priceStr), 0);
            } else {
                const char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nProduct not found";
                send(clientSocket, response, strlen(response), 0);
            }
        } else {
            const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid request";
            send(clientSocket, response, strlen(response), 0);
        }
    }
    close(clientSocket);
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrSize = sizeof(struct sockaddr_in);

    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("bind failed");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket, 5) < 0) {
        perror("listen failed");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrSize);
        if (clientSocket < 0) {
            perror("accept failed");
            continue;
        }
        handleClient(clientSocket);
    }

    close(serverSocket);
    return 0;
}