#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024

float getPrice(const char *productCode) {
    if (strcmp(productCode, "A") == 0) return 10.0;
    if (strcmp(productCode, "B") == 0) return 20.0;
    if (strcmp(productCode, "C") == 0) return 30.0;
    return 0.0;
}

float calculateTotal(const char *productCode, int quantity) {
    float price = getPrice(productCode);
    return price * quantity;
}

void handleRequest(int clientSocket) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);

    read(clientSocket, buffer, BUFFER_SIZE - 1);
    printf("Received: %s\n", buffer);

    const char *productCode = "A";
    int quantity = 2;
    sscanf(buffer, "%s %d", productCode, &quantity);

    float total = calculateTotal(productCode, quantity);

    char response[BUFFER_SIZE];
    snprintf(response, BUFFER_SIZE, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nPrice for %s * %d: %.2f", productCode, quantity, total);
    write(clientSocket, response, strlen(response));

    close(clientSocket);
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(struct sockaddr_in);

    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
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

    printf("Server listening on port %d\n", PORT);

    while (1) {
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrLen);
        if (clientSocket < 0) {
            perror("Accept failed");
            continue;
        }
        handleRequest(clientSocket);
    }

    close(serverSocket);
    return 0;
}