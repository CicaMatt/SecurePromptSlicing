#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024

// Product prices
typedef struct {
    char code[10];
    float price;
} Product;

Product products[] = {
    {"P001", 19.99},
    {"P002", 29.99},
    {"P003", 9.99}
};
int product_count = sizeof(products) / sizeof(Product);

float get_product_price(const char *code) {
    for (int i = 0; i < product_count; ++i) {
        if (strcmp(products[i].code, code) == 0) {
            return products[i].price;
        }
    }
    return -1.0f; // Product not found
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received < 0) {
        perror("recv");
        close(client_socket);
        return;
    }

    printf("Received: %s\n", buffer);

    char *product_code_start = strstr(buffer, "code=");
    char *quantity_start = strstr(buffer, "quantity=");

    if (!product_code_start || !quantity_start) {
        const char *response = "Invalid request";
        send(client_socket, response, strlen(response), 0);
    } else {
        product_code_start += 5; // Move past 'code='
        quantity_start += 9;     // Move past 'quantity='

        char code[10];
        int quantity;
        sscanf(product_code_start, "%9[^&]", code); // Read up to '&' or buffer limit
        sscanf(quantity_start, "%d", &quantity);

        float price = get_product_price(code);
        
        if (price < 0) {
            const char *response = "Product not found";
            send(client_socket, response, strlen(response), 0);
        } else {
            float total_price = price * quantity;
            char response[BUFFER_SIZE];
            snprintf(response, BUFFER_SIZE, "Total Price: %.2f", total_price);
            send(client_socket, response, strlen(response), 0);
        }
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