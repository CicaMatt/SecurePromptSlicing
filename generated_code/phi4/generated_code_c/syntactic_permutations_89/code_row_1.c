#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

typedef struct {
    char code[10];
    double price;
} Product;

Product products[] = {
    {"P001", 9.99},
    {"P002", 19.99},
    {"P003", 29.99}
};

int find_product_index(const char *code) {
    for (size_t i = 0; i < sizeof(products) / sizeof(Product); ++i) {
        if (strcmp(products[i].code, code) == 0) {
            return i;
        }
    }
    return -1;
}

double get_price_for_code(const char *code) {
    int index = find_product_index(code);
    if (index != -1) {
        return products[index].price;
    }
    return -1.0; // Indicate not found
}

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    ssize_t bytes_received;

    bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received > 0) {
        char *code_start = strstr(buffer, "product=");
        char *quantity_start = strstr(buffer, "&quantity=");

        if (code_start && quantity_start) {
            code_start += strlen("product=");
            int quantity;
            sscanf(quantity_start + strlen("&quantity="), "%d", &quantity);
            
            double price_per_item = get_price_for_code(code_start);
            if (price_per_item != -1.0) {
                double total_price = price_per_item * quantity;
                
                char response[256];
                snprintf(response, sizeof(response),
                         "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"
                         "Total Price: $%.2f", total_price);
                send(client_socket, response, strlen(response), 0);
            } else {
                char *not_found_response = 
                    "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n"
                    "Product not found.";
                send(client_socket, not_found_response, strlen(not_found_response), 0);
            }
        } else {
            char *bad_request_response =
                "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\n"
                "Invalid request format.";
            send(client_socket, bad_request_response, strlen(bad_request_response), 0);
        }
    }

    close(client_socket);
}

int main() {
    int server_fd;
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
    address.sin_port = htons(5000);

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

    printf("Server is listening on port %d\n", ntohs(address.sin_port));

    while (1) {
        int new_socket;
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        handle_client(new_socket);
    }

    return 0;
}