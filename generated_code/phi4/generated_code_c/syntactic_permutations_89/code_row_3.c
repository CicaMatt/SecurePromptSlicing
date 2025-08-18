#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 5000

// Simulated product database
typedef struct {
    char code[10];
    float price;
} Product;

Product products[] = {
    {"A001", 9.99},
    {"B002", 19.99},
    {"C003", 29.99}
};

int num_products = sizeof(products) / sizeof(Product);

// Function to find the price of a product by its code
float get_price_by_code(const char *code) {
    for (int i = 0; i < num_products; ++i) {
        if (strcmp(products[i].code, code) == 0) {
            return products[i].price;
        }
    }
    return -1.0; // Return -1 if product not found
}

// Simple HTTP request handler
void handle_request(int client_sock) {
    char buffer[1024] = {0};
    read(client_sock, buffer, sizeof(buffer));

    const char *method = strtok(buffer, " ");
    const char *path = strtok(NULL, " ");
    const char *version = strtok(NULL, "\r\n");

    if (strcmp(method, "GET") == 0 && strstr(path, "/price?")) {
        char product_code[10] = {0};
        int quantity;
        
        sscanf(strstr(path, "code=") + 5, "%9[^&]", product_code);
        sscanf(strstr(path, "quantity=") + 10, "%d", &quantity);

        float price_per_item = get_price_by_code(product_code);
        if (price_per_item != -1.0) {
            float total_price = price_per_item * quantity;
            char response[512];
            snprintf(response, sizeof(response),
                     "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nTotal Price: $%.2f", total_price);
            send(client_sock, response, strlen(response), 0);
        } else {
            const char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nProduct not found";
            send(client_sock, response, strlen(response), 0);
        }
    } else {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nBad request";
        send(client_sock, response, strlen(response), 0);
    }

    close(client_sock);
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

    printf("Listening on port %d...\n", PORT);

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