#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5000

typedef struct {
    const char *code;
    double price;
} Product;

Product products[] = {
    {"P001", 10.99},
    {"P002", 5.49},
    {"P003", 7.89}
};

int find_product_index(const char *code) {
    for (int i = 0; i < sizeof(products) / sizeof(Product); i++) {
        if (strcmp(products[i].code, code) == 0) {
            return i;
        }
    }
    return -1;
}

double get_price_for_code(const char *code) {
    int index = find_product_index(code);
    if (index != -1) {
        return products[index].price;
    } else {
        printf("Product not found\n");
        exit(EXIT_FAILURE);
    }
}

void handle_request(int client_fd) {
    char buffer[1024] = {0};
    read(client_fd, buffer, sizeof(buffer));

    char product_code[10];
    int quantity;

    sscanf(buffer, "GET /product?code=%s&quantity=%d HTTP/1.1", product_code, &quantity);

    double price = get_price_for_code(product_code);
    double total_price = price * quantity;

    char response[1024];
    snprintf(response, sizeof(response),
             "HTTP/1.1 200 OK\nContent-Type: text/plain\n\nTotal Price: %.2f", total_price);

    write(client_fd, response, strlen(response));

    close(client_fd);
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

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        
        handle_request(new_socket);
    }

    close(server_fd);
    return 0;
}