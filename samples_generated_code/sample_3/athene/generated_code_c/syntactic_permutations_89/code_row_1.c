#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024

float get_price(const char *product_code) {
    if (strcmp(product_code, "A") == 0) return 10.99;
    if (strcmp(product_code, "B") == 0) return 19.95;
    if (strcmp(product_code, "C") == 0) return 25.50;
    return -1; // Invalid product code
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(client_socket, buffer, BUFFER_SIZE)) > 0) {
        buffer[bytes_read] = '\0';
        if (strstr(buffer, "GET /price") != NULL) {
            char product_code[10], quantity_str[10];
            float price, total;
            int quantity;

            sscanf(buffer, "GET /price?product=%[^&]&quantity=%[^\n]", product_code, quantity_str);
            price = get_price(product_code);
            if (price == -1) {
                const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 23\r\n\r\nInvalid product code.\n";
                write(client_socket, response, strlen(response));
                break;
            }

            quantity = atoi(quantity_str);
            total = price * quantity;

            char response[512];
            snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: %zu\r\n\r\nTotal Price: %.2f", strlen("Total Price: ") + 6, total);
            write(client_socket, response, strlen(response));
            break;
        }
    }

    close(client_socket);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 5) == -1) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (client_fd < 0) {
            perror("Accept failed");
            continue;
        }
        handle_client(client_fd);
    }

    close(server_fd);
    return 0;
}