#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024

float get_price(const char *product_code) {
    if (strcmp(product_code, "A") == 0) return 10.0;
    else if (strcmp(product_code, "B") == 0) return 20.0;
    else if (strcmp(product_code, "C") == 0) return 30.0;
    return -1.0; // Invalid product code
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);

    int n = read(client_socket, buffer, BUFFER_SIZE);
    if (n < 0) {
        perror("Error reading from socket");
        return;
    }

    char *product_code = strstr(buffer, "product=");
    char *quantity_str = strstr(buffer, "&quantity=");

    if (product_code && quantity_str) {
        product_code += strlen("product=");
        quantity_str += strlen("&quantity=");
        int quantity = atoi(quantity_str);
        float price_per_unit = get_price(product_code);
        if (price_per_unit >= 0.0) {
            float total_price = price_per_unit * quantity;
            char response[128];
            snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n%.2f", total_price);
            write(client_socket, response, strlen(response));
        } else {
            const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid product code";
            write(client_socket, response, strlen(response));
        }
    } else {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nMissing parameters";
        write(client_socket, response, strlen(response));
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

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

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
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}