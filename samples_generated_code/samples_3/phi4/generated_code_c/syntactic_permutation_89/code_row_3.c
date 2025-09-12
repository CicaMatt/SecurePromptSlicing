#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

typedef struct {
    char product_code[10];
    double price;
} Product;

Product products[] = {
    {"P001", 19.99},
    {"P002", 29.99},
    {"P003", 9.99}
};

int get_product_price(char *product_code) {
    for (int i = 0; i < sizeof(products)/sizeof(products[0]); i++) {
        if (strcmp(products[i].product_code, product_code) == 0) {
            return products[i].price;
        }
    }
    return -1.0;
}

void handle_request(int client_socket) {
    char buffer[1024] = {0};
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

    if (bytes_received > 0) {
        char *product_code_start = strstr(buffer, "GET /?code=");
        char *quantity_start = strstr(buffer, "&qty=");

        if (product_code_start && quantity_start) {
            product_code_start += strlen("GET /?code=");
            int product_code_len = quantity_start - product_code_start;
            char product_code[10];
            strncpy(product_code, product_code_start, product_code_len);
            product_code[product_code_len] = '\0';

            int qty_start = quantity_start + strlen("&qty=");
            int qty_end = strstr(quantity_start, " HTTP") - qty_start;
            double quantity = atof(qty_start);

            double price_per_unit = get_product_price(product_code);
            if (price_per_unit >= 0) {
                double total_cost = price_per_unit * quantity;

                char response[512];
                snprintf(response, sizeof(response),
                    "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nTotal Cost: $%.2f", total_cost);
                send(client_socket, response, strlen(response), 0);
            } else {
                char *not_found_response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nProduct not found";
                send(client_socket, not_found_response, strlen(not_found_response), 0);
            }
        } else {
            char *bad_request_response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid request format";
            send(client_socket, bad_request_response, strlen(bad_request_response), 0);
        }
    }

    close(client_socket);
}

int main() {
    int server_fd;
    struct sockaddr_in address;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

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

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        int client_socket;
        struct sockaddr_in client_address;
        socklen_t client_addr_len = sizeof(client_address);

        if ((client_socket = accept(server_fd, (struct sockaddr *)&client_address, &client_addr_len)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        handle_request(client_socket);
    }

    return 0;
}