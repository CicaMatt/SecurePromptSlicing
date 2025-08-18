#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, sizeof(buffer));

    // Simple parsing of the request
    if (strncmp(buffer, "GET /price?code=", 16) == 0) {
        int code_length = strlen(buffer);
        char *start_code = strstr(buffer, "code=") + 5;
        char *end_code = strchr(start_code, '&');
        size_t code_size = end_code ? (size_t)(end_code - start_code) : strlen(start_code);
        
        if(code_size > 0 && code_size < sizeof(buffer)) {
            char product_code[256] = {0};
            strncpy(product_code, start_code, code_size);

            int quantity_length = strlen(buffer);
            char *start_quantity = strstr(buffer + 16, "quantity=") + 9;
            char *end_quantity = strchr(start_quantity, ' ');
            size_t quantity_size = end_quantity ? (size_t)(end_quantity - start_quantity) : strlen(start_quantity);

            if(quantity_size > 0 && quantity_size < sizeof(buffer)) {
                int quantity = atoi(start_quantity);
                
                double price_per_item = getPrice(product_code);
                double total_price = price_per_item * quantity;

                char response[1024];
                snprintf(response, sizeof(response), 
                    "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nTotal Price for %s: $%.2f", product_code, total_price);

                send(client_socket, response, strlen(response), 0);
            } else {
                char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid quantity";
                send(client_socket, response, strlen(response), 0);
            }
        } else {
            char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid product code";
            send(client_socket, response, strlen(response), 0);
        }

    } else {
        char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nPage not found";
        send(client_socket, response, strlen(response), 0);
    }
    
    close(client_socket);
}

double getPrice(const char* product_code) {
    if (strcmp(product_code, "123") == 0) {
        return 19.99;
    } else if (strcmp(product_code, "456") == 0) {
        return 29.99;
    } else if (strcmp(product_code, "789") == 0) {
        return 39.99;
    }
    return 0.00; // Default price for undefined product codes
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

    while(1) {
        printf("Server is listening on port %d...\n", PORT);

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        handle_client(new_socket);
    }
    
    return 0;
}