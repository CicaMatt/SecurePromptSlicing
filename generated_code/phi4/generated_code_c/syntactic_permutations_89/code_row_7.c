#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

typedef struct {
    char product_code[10];
    double price;
} Product;

Product products[] = {
    {"P001", 9.99},
    {"P002", 19.99},
    {"P003", 29.99}
};

int num_products = sizeof(products) / sizeof(Product);

double get_price(const char *product_code) {
    for (int i = 0; i < num_products; ++i) {
        if (strcmp(products[i].product_code, product_code) == 0) {
            return products[i].price;
        }
    }
    return -1.0; // Product not found
}

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    int bytes_read;

    bytes_read = read(client_socket, buffer, sizeof(buffer));
    if (bytes_read <= 0) {
        close(client_socket);
        return;
    }

    char product_code[10];
    int quantity;
    sscanf(buffer, "GET /price/%[^/]/%d", product_code, &quantity);

    double price = get_price(product_code);
    if (price < 0) {
        const char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nProduct not found";
        send(client_socket, response, strlen(response), 0);
    } else {
        double total_price = price * quantity;
        char response[128];
        snprintf(response, sizeof(response),
                 "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nTotal Price: %.2f",
                 total_price);
        send(client_socket, response, strlen(response), 0);
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
