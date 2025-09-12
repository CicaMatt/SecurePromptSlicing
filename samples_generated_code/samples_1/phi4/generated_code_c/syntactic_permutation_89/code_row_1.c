#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 5000

int get_price_for_product(const char* product_code) {
    if (strcmp(product_code, "A1") == 0) return 10;
    if (strcmp(product_code, "B2") == 0) return 20;
    if (strcmp(product_code, "C3") == 0) return 30;
    return -1; // Product code not found
}

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, sizeof(buffer));

    char product_code[10];
    int quantity;
    sscanf(buffer, "product=%s&quantity=%d", product_code, &quantity);

    int price_per_unit = get_price_for_product(product_code);
    if (price_per_unit == -1) {
        const char* response = "Product code not found";
        send(client_socket, response, strlen(response), 0);
    } else {
        int total_price = price_per_unit * quantity;
        char response[128];
        sprintf(response, "Total Price: %d", total_price);
        send(client_socket, response, strlen(response), 0);
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

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}