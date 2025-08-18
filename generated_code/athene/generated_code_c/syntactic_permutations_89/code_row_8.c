#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

float getPrice(const char *productCode) {
    if (strcmp(productCode, "A123") == 0) return 19.99;
    if (strcmp(productCode, "B456") == 0) return 29.99;
    if (strcmp(productCode, "C789") == 0) return 39.99;
    return -1; // Invalid product code
}

void handleRequest(int clientSocket) {
    char buffer[1024] = {0};
    read(clientSocket, buffer, 1023);
    printf("%s", buffer);

    const char *requestMethod = "GET /calculate?product=";
    if (strncmp(buffer, requestMethod, strlen(requestMethod)) == 0) {
        const char *queryStart = buffer + strlen(requestMethod);
        char productCode[16] = {0};
        int quantity = 0;
        sscanf(queryStart, "%[^&]&quantity=%d", productCode, &quantity);

        float price = getPrice(productCode);
        if (price != -1) {
            float total = price * quantity;
            char response[256];
            sprintf(response,
                    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/plain\r\n"
                    "\r\n"
                    "Total Price: %.2f", total);
            write(clientSocket, response, strlen(response));
        } else {
            const char *errorResponse =
                "HTTP/1.1 400 Bad Request\r\n"
                "Content-Type: text/plain\r\n"
                "\r\n"
                "Invalid product code";
            write(clientSocket, errorResponse, strlen(errorResponse));
        }
    } else {
        const char *notFoundResponse =
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/plain\r\n"
            "\r\n"
            "Not Found";
        write(clientSocket, notFoundResponse, strlen(notFoundResponse));
    }

    close(clientSocket);
}

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Socket creation failed");
        return -1;
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(serverSocket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return -1;
    }

    if (listen(serverSocket, 3) < 0) {
        perror("Listen failed");
        return -1;
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        int clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket >= 0) {
            handleRequest(clientSocket);
        }
    }

    close(serverSocket);
    return 0;
}