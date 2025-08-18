#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024

float getPriceForProduct(const char *productCode) {
    if (strcmp(productCode, "A123") == 0) return 9.99;
    if (strcmp(productCode, "B456") == 0) return 14.99;
    if (strcmp(productCode, "C789") == 0) return 19.99;
    return -1; // Invalid product code
}

void handleClient(int clientSocket) {
    char buffer[BUFFER_SIZE] = {0};
    read(clientSocket, buffer, BUFFER_SIZE);
    printf("Received: %s\n", buffer);

    const char *productCodeStart = strstr(buffer, "product=");
    if (productCodeStart == NULL) goto sendError;

    const char *quantityStart = strstr(buffer, "&quantity=");
    if (quantityStart == NULL) goto sendError;

    int productCodeLength = quantityStart - productCodeStart - 8; // Length of "product="
    char productCode[10];
    strncpy(productCode, productCodeStart + 8, productCodeLength);
    productCode[productCodeLength] = '\0';

    const char *quantityStr = quantityStart + 9; // Length of "&quantity="
    int quantity;
    sscanf(quantityStr, "%d", &quantity);

    float price = getPriceForProduct(productCode);
    if (price == -1) goto sendError;

    float totalCost = price * quantity;
    char response[256];
    snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nTotal cost: %.2f", totalCost);

    write(clientSocket, response, strlen(response));
    close(clientSocket);
    return;

sendError:
    const char *errorResponse = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid request";
    write(clientSocket, errorResponse, strlen(errorResponse));
    close(clientSocket);
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(struct sockaddr_in);

    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket, 3) < 0) {
        perror("Listen failed");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrLen);
        if (clientSocket < 0) {
            perror("Accept failed");
            continue;
        }
        handleClient(clientSocket);
    }

    close(serverSocket);
    return 0;
}