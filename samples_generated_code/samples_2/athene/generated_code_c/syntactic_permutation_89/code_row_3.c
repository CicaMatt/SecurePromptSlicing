#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024

float get_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    if (strcmp(product_code, "B456") == 0) return 14.99;
    if (strcmp(product_code, "C789") == 0) return 19.99;
    return -1.0; // Invalid product code
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE);

    const char *product_code = NULL;
    int quantity = 0;

    sscanf(buffer, "GET /price?code=%s&qty=%d HTTP/1.1", &product_code, &quantity);

    float price = get_price(product_code);
    if (price < 0) {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 25\r\n\r\nInvalid product code or quantity.";
        send(client_socket, response, strlen(response), 0);
    } else {
        float total_price = price * quantity;
        char response[256];
        snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Length: %zu\r\n\r\n%.2f", strlen("%.2f"), total_price);
        send(client_socket, response, strlen(response), 0);
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            continue;
        }
        handle_request(new_socket);
    }

    close(server_fd);
    return 0;
}