#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

float get_price(const char *product_code) {
    if (strcmp(product_code, "ABC123") == 0) return 10.5;
    else if (strcmp(product_code, "XYZ789") == 0) return 15.75;
    else return 0.0; // Default price for unknown product code
}

float calculate_price(const char *product_code, int quantity) {
    float price = get_price(product_code);
    if (price > 0) {
        return price * quantity;
    } else {
        fprintf(stderr, "Unknown product code: %s\n", product_code);
        return -1.0; // Indicate error
    }
}

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    
    int valread = read(client_socket, buffer, 1023);
    if (valread > 0) {
        printf("Request: %s\n", buffer);

        // Parse request, expecting format "GET /calculate?code=CODE&quantity=QTY"
        char *method = strtok(buffer, " ");
        char *uri = strtok(NULL, " ");
        
        if (strcmp(method, "GET") == 0 && strstr(uri, "/calculate")) {
            const char *product_code = NULL;
            int quantity = 1;

            char *query = strchr(uri, '?') + 1;
            char *param = strtok(query, "&");

            while (param) {
                if (strncmp(param, "code=", 5) == 0) {
                    product_code = param + 5;
                } else if (strncmp(param, "quantity=", 9) == 0) {
                    quantity = atoi(param + 9);
                }
                param = strtok(NULL, "&");
            }

            if (product_code) {
                float final_price = calculate_price(product_code, quantity);
                char response[1024];
                
                if (final_price >= 0) {
                    snprintf(response, sizeof(response),
                             "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"
                             "Total Price: $%.2f", final_price);
                } else {
                    snprintf(response, sizeof(response), 
                             "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\n"
                             "Invalid product code.");
                }
                
                send(client_socket, response, strlen(response), 0);
            } else {
                const char *no_code_response = 
                    "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\n"
                    "Product code is required.";
                send(client_socket, no_code_response, strlen(no_code_response), 0);
            }
        } else {
            const char *not_found_response =
                "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n"
                "Not Found";
            send(client_socket, not_found_response, strlen(not_found_response), 0);
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

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        if (new_socket < 0) {
            perror("accept");
            continue;
        }
        
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}