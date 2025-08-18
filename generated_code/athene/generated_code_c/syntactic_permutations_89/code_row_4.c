#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

float getPrice(const char *productCode) {
    if (strcmp(productCode, "A123") == 0) return 9.99;
    if (strcmp(productCode, "B456") == 0) return 14.99;
    if (strcmp(productCode, "C789") == 0) return 19.99;
    return -1; // Product not found
}

void handleRequest(int clientSocket) {
    char buffer[1024];
    int n;

    bzero(buffer, sizeof(buffer));
    read(clientSocket, buffer, sizeof(buffer)-1);

    const char *productCode = "A123"; // Default product code for testing
    int quantity = 1; // Default quantity for testing

    // Parse the request to get product code and quantity (simplified)
    sscanf(buffer, "%*s %*s %s", buffer);
    if (sscanf(buffer, "/?productCode=%[^&]&quantity=%d", productCode, &quantity) != 2) {
        send(clientSocket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n", 45, 0);
        close(clientSocket);
        return;
    }

    float price = getPrice(productCode);
    if (price == -1) {
        send(clientSocket, "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n", 39, 0);
    } else {
        char response[256];
        sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: %zd\r\n\r\nTotal Price: %.2f",
                strlen("Total Price: ") + 7, price * quantity);
        send(clientSocket, response, strlen(response), 0);
    }
    close(clientSocket);
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(struct sockaddr_in);

    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        return -1;
    }

    memset(&serverAddr, '0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("bind failed");
        return -1;
    }

    if (listen(serverSocket, 3) < 0) {
        perror("listen failed");
        return -1;
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrLen);
        if (clientSocket < 0) {
            perror("accept failed");
            continue;
        }
        handleRequest(clientSocket);
    }

    close(serverSocket);
    return 0;
}