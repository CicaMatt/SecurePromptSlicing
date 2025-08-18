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
    {"P001", 100.0},
    {"P002", 200.5},
    {"P003", 150.75}
};

int get_product_count() {
    return sizeof(products) / sizeof(Product);
}

float get_price_for_code(const char *code) {
    for (int i = 0; i < get_product_count(); ++i) {
        if (strcmp(products[i].product_code, code) == 0) {
            return products[i].price;
        }
    }
    return -1.0; // Product not found
}

float calculate_total_price(const char *code, int quantity) {
    float price = get_price_for_code(code);
    if (price == -1.0) {
        printf("Product code %s not found.\n", code);
        exit(1);
    }
    return price * quantity;
}

void handle_client(int client_sock) {
    char buffer[1024] = {0};
    int read_size;

    // Read request
    if ((read_size = recv(client_sock, buffer, sizeof(buffer), 0)) > 0) {
        buffer[read_size] = '\0';
        
        // Parse product code and quantity from the request
        char product_code[10];
        int quantity;
        sscanf(buffer, "GET /price?code=%9[^&]&quantity=%d", product_code, &quantity);

        // Calculate total price
        float total_price = calculate_total_price(product_code, quantity);
        
        // Prepare response
        char response[256];
        snprintf(response, sizeof(response), 
                 "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nTotal Price: %.2f", total_price);

        // Send response
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

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        
        handle_client(new_socket);
    }

    return 0;
}