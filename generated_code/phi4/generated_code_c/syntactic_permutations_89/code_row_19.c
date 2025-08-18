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

float get_price(const char *product_code) {
    // Example products and their prices
    Product products[] = {
        {"A001", 9.99},
        {"B002", 19.99},
        {"C003", 29.99}
    };
    
    int num_products = sizeof(products) / sizeof(Product);
    
    for (int i = 0; i < num_products; ++i) {
        if (strcmp(products[i].product_code, product_code) == 0) {
            return products[i].price;
        }
    }
    
    return -1.0; // Return -1 if product not found
}

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    
    if (bytes_received > 0) {
        char *token = strtok(buffer, " ");
        float quantity = atof(strtok(NULL, " "));
        
        if (strcmp(token, "/calculate_price") == 0 && token != NULL) {
            char product_code[10] = {0};
            strcpy(product_code, strtok(NULL, " "));

            float price_per_unit = get_price(product_code);
            
            if (price_per_unit >= 0) {
                float total_price = price_per_unit * quantity;
                char response[128];
                snprintf(response, sizeof(response), "Total Price: $%.2f", total_price);
                
                send(client_socket, response, strlen(response), 0);
            } else {
                char response[] = "Product not found";
                send(client_socket, response, strlen(response), 0);
            }
        } else {
            char *response = "Invalid request";
            send(client_socket, response, strlen(response), 0);
        }
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
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    printf("Server is listening on port %d\n", PORT);

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