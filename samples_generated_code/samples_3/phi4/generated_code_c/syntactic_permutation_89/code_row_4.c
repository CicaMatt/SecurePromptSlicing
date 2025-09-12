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
    {"A001", 9.99},
    {"B002", 19.99},
    {"C003", 29.99}
};

int get_product_count() {
    return sizeof(products) / sizeof(Product);
}

float get_price(const char *product_code) {
    int count = get_product_count();
    for (int i = 0; i < count; ++i) {
        if (strcmp(products[i].product_code, product_code) == 0) {
            return products[i].price;
        }
    }
    return -1.0f; // Product not found
}

float calculate_price(const char *request) {
    char product_code[10];
    int quantity = 0;

    sscanf(request, "/%9[^/]/%d", product_code, &quantity);
    float price_per_unit = get_price(product_code);

    if (price_per_unit == -1.0f) {
        return -1.0f; // Product not found
    }

    return price_per_unit * quantity;
}

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, 1024);

    float total_price = calculate_price(buffer);
    
    if (total_price == -1.0f) {
        const char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nProduct not found.\n";
        write(client_socket, response, strlen(response));
    } else {
        char response[128];
        snprintf(response, sizeof(response), 
                 "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nTotal Price: %.2f\n", total_price);
        write(client_socket, response, strlen(response));
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

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        handle_client(new_socket);
    }

    return 0;
}