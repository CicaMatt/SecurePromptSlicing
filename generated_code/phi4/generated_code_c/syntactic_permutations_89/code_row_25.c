#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    
    if (bytes_received > 0) {
        // Parse request
        printf("Received: %s\n", buffer);

        // Simple HTTP parsing
        char *method = strtok(buffer, " ");
        char *path = strtok(NULL, " ");
        char *version = strtok(NULL, "\r\n");

        char product_code[16];
        int quantity;
        sscanf(path, "/product/%15[^/]/%d", product_code, &quantity);

        double price_per_unit = get_price_for_product(product_code);
        if (price_per_unit != -1) {
            double total_price = price_per_unit * quantity;
            char response[512];
            snprintf(response, sizeof(response),
                     "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"
                     "Product Code: %s\nQuantity: %d\nPrice per unit: %.2f\nTotal Price: %.2f",
                     product_code, quantity, price_per_unit, total_price);
            send(client_socket, response, strlen(response), 0);
        } else {
            char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nProduct not found.";
            send(client_socket, response, strlen(response), 0);
        }
    }

    close(client_socket);
}

double get_price_for_product(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) {
        return 10.50;
    } else if (strcmp(product_code, "B456") == 0) {
        return 15.75;
    } else if (strcmp(product_code, "C789") == 0) {
        return 7.25;
    }
    return -1; // Product not found
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Binding the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listening for connections
    if (listen(server_fd, 10) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}