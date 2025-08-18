#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

void handle_request(int client_fd) {
    char buffer[1024];
    int bytes_received = read(client_fd, buffer, sizeof(buffer));
    if (bytes_received <= 0) return;

    char product_code[16], quantity_str[16];
    sscanf(buffer, "GET /calculate?code=%s&quantity=%s HTTP/1.1", product_code, quantity_str);

    int quantity = atoi(quantity_str);
    long result = 42 * quantity; // Simple calculation for demonstration

    char response[1024];
    snprintf(response, sizeof(response),
             "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nProduct Code: %s\nQuantity: %d\nResult: %ld",
             product_code, quantity, result);

    write(client_fd, response, strlen(response));
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    printf("Server listening on port %d\n", PORT);

    while (1) {
        int client_fd = accept(server_fd, NULL, NULL);
        if (client_fd < 0) {
            perror("Accept failed");
            continue;
        }

        handle_request(client_fd);
        close(client_fd);
    }

    close(server_fd);
    return 0;
}