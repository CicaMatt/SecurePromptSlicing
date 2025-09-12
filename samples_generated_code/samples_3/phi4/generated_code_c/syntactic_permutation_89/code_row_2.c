#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

typedef struct {
    int price;
    int quantity;
} Order;

int calculate_price(int base_price, int quantity) {
    return base_price * quantity;
}

void handle_request(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, sizeof(buffer));
    
    printf("Received: %s\n", buffer);

    if (strncmp(buffer, "GET /order?base_price=", 21) == 0) {
        int base_price;
        sscanf(buffer + 21, "%d&quantity=%d", &base_price, &(Order){.price = base_price}.quantity);
        
        int total_price = calculate_price(base_price, (Order){.price = base_price}.quantity);

        char response[1024];
        snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nTotal Price: %d", total_price);
        
        send(client_socket, response, strlen(response), 0);
    } else {
        char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot Found";
        send(client_socket, response, strlen(response), 0);
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        handle_request(new_socket);

        close(new_socket);
    }

    return 0;
}