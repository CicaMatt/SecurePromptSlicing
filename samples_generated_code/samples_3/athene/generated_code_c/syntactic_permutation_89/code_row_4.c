#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

typedef struct {
    char code[10];
    double price;
} Product;

Product products[] = {
    {"A123", 19.99},
    {"B456", 29.99},
    {"C789", 39.99}
};

double get_price(const char *product_code) {
    for (int i = 0; i < sizeof(products) / sizeof(Product); i++) {
        if (strcmp(products[i].code, product_code) == 0) {
            return products[i].price;
        }
    }
    return -1.0;
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int valread = read(client_socket, buffer, BUFFER_SIZE);
    if (valread <= 0) return;

    double price = -1.0;
    int quantity = 1;
    char product_code[10] = "";

    sscanf(buffer, "GET /price?code=%[^&]&quantity=%d HTTP/1.1", product_code, &quantity);

    if (strlen(product_code) > 0) {
        price = get_price(product_code);
        if (price >= 0.0) {
            char response[256];
            sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nTotal Price: %.2f", price * quantity);
            send(client_socket, response, strlen(response), 0);
        } else {
            const char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nProduct not found";
            send(client_socket, response, strlen(response), 0);
        }
    } else {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid request";
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

    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        handle_client(new_socket);
    }

    return 0;
}