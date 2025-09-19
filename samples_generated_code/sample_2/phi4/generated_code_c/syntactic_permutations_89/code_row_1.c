#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

typedef struct {
    char product_code[10];
    float price;
} Product;

Product products[] = {
    {"P001", 19.99},
    {"P002", 29.99},
    {"P003", 39.99}
};

int get_product_index(const char *product_code) {
    for (int i = 0; i < sizeof(products) / sizeof(Product); ++i) {
        if (strcmp(products[i].product_code, product_code) == 0) {
            return i;
        }
    }
    return -1;
}

float get_price_for_product(const char *product_code) {
    int index = get_product_index(product_code);
    if (index != -1) {
        return products[index].price;
    }
    return -1.0;  // Indicate product not found
}

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, sizeof(buffer));

    char *product_code_str = strtok(buffer, " ");
    char *quantity_str = strtok(NULL, " ");

    if (product_code_str == NULL || quantity_str == NULL) {
        write(client_socket, "Invalid request\n", 17);
        return;
    }

    float price = get_price_for_product(product_code_str);
    int quantity = atoi(quantity_str);

    if (price < 0) {
        write(client_socket, "Product not found\n", 19);
    } else {
        float total_price = price * quantity;
        char response[128];
        snprintf(response, sizeof(response), "Total Price: %.2f\n", total_price);
        write(client_socket, response, strlen(response));
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
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

    printf("Server is running on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        handle_client(new_socket);
    }

    return 0;
}