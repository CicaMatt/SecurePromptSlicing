#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

typedef struct {
    char product_code[10];
    int quantity;
} Product;

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    recv(client_socket, buffer, sizeof(buffer), 0);

    Product p;
    sscanf(buffer, "GET /calculate?product_code=%9s&quantity=%d HTTP/1.1", p.product_code, &p.quantity);

    int result = calculate_product_cost(p.product_code, p.quantity);
    char response[1024];
    snprintf(response, sizeof(response), 
             "HTTP/1.1 200 OK\nContent-Type: text/plain\n\nProduct Code: %s\nQuantity: %d\nTotal Cost: %d",
             p.product_code, p.quantity, result);

    send(client_socket, response, strlen(response), 0);
    close(client_socket);
}

int calculate_product_cost(const char *product_code, int quantity) {
    // Simple cost calculation based on product code
    if (strcmp(product_code, "A123") == 0) return 10 * quantity;
    if (strcmp(product_code, "B456") == 0) return 20 * quantity;
    if (strcmp(product_code, "C789") == 0) return 30 * quantity;
    return 0; // Default cost
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) continue;

        handle_client(new_socket);
    }

    return 0;
}