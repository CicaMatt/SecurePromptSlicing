#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024

float get_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 29.99;
    if (strcmp(product_code, "C789") == 0) return 39.99;
    return -1.0; // Invalid product code
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE);
    
    const char *start = strstr(buffer, "GET /price?code=");
    if (start == NULL) {
        write(client_socket, "HTTP/1.1 404 Not Found\r\nContent-Length: 25\r\n\r\nInvalid request.", 68);
        close(client_socket);
        return;
    }

    char *query_start = strstr(start, "code=");
    if (query_start == NULL) {
        write(client_socket, "HTTP/1.1 404 Not Found\r\nContent-Length: 25\r\n\r\nInvalid request.", 68);
        close(client_socket);
        return;
    }

    query_start += strlen("code=");
    char *quantity_param = strstr(query_start, "&quantity=");
    if (quantity_param == NULL) {
        write(client_socket, "HTTP/1.1 404 Not Found\r\nContent-Length: 25\r\n\r\nInvalid request.", 68);
        close(client_socket);
        return;
    }

    *quantity_param = '\0';
    quantity_param += strlen("&quantity=");

    char product_code[10];
    int quantity;
    strcpy(product_code, query_start);
    sscanf(quantity_param, "%d", &quantity);

    float price = get_price(product_code);
    if (price < 0) {
        write(client_socket, "HTTP/1.1 404 Not Found\r\nContent-Length: 27\r\n\r\nProduct code not found.", 70);
    } else {
        char response[BUFFER_SIZE];
        snprintf(response, BUFFER_SIZE, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: %zu\r\n\r\nTotal Price: %.2f", 14 + strlen("%.2f"), price * quantity);
        write(client_socket, response, strlen(response));
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}