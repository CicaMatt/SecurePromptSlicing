#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5000

typedef struct {
    char code[10];
    double price;
} Product;

Product products[] = {
    {"P001", 100.50},
    {"P002", 200.75},
    {"P003", 150.00}
};

int get_product_index(const char *code) {
    for (int i = 0; i < sizeof(products) / sizeof(Product); ++i) {
        if (strcmp(products[i].code, code) == 0) {
            return i;
        }
    }
    return -1;
}

double calculate_price(const char *product_code, int quantity) {
    int index = get_product_index(product_code);
    if (index != -1) {
        return products[index].price * quantity;
    }
    return -1.0; // Error value
}

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, 1024);

    char product_code[10];
    int quantity;

    sscanf(buffer, "/get_price?code=%s&quantity=%d", product_code, &quantity);
    
    double price = calculate_price(product_code, quantity);

    if (price >= 0) {
        char response[256];
        snprintf(response, sizeof(response), "Price: %.2f\n", price);
        send(client_socket, response, strlen(response), 0);
    } else {
        const char *response = "Product not found\n";
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

    printf("Server listening on port %d\n", PORT);

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