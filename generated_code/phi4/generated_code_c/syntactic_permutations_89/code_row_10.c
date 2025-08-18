#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024

struct product {
    char code[10];
    float price;
};

struct product products[] = {
    {"P001", 9.99},
    {"P002", 19.99},
    {"P003", 29.99}
};

int get_product_index(const char *code) {
    for (size_t i = 0; i < sizeof(products)/sizeof(struct product); ++i) {
        if (strcmp(products[i].code, code) == 0) {
            return i;
        }
    }
    return -1;
}

float calculate_price(const char *product_code, int quantity) {
    int index = get_product_index(product_code);
    if (index != -1 && quantity > 0) {
        return products[index].price * quantity;
    } else {
        return -1.0f; // Indicate error
    }
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    bzero(buffer, BUFFER_SIZE);

    read(client_socket, buffer, BUFFER_SIZE);
    printf("Received: %s\n", buffer);

    char *token = strtok(buffer, " ");
    if (token == NULL || strlen(token) != 4) { // Expecting a product code of length 4
        write(client_socket, "Invalid request\n", 16);
        close(client_socket);
        return;
    }

    token = strtok(NULL, " ");
    int quantity = atoi(token);

    float price = calculate_price(token, quantity);
    if (price != -1.0f) {
        char response[64];
        snprintf(response, sizeof(response), "Total price: %.2f\n", price);
        write(client_socket, response, strlen(response));
    } else {
        write(client_socket, "Product not found or invalid quantity\n", 35);
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

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
    
    while (1) {
        printf("Waiting for connections...\n");

        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }

        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}