#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024

float get_price(const char *product_code) {
    if (strcmp(product_code, "A") == 0) return 10.5;
    else if (strcmp(product_code, "B") == 0) return 20.75;
    else if (strcmp(product_code, "C") == 0) return 5.25;
    return -1; // Invalid product code
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    read(client_socket, buffer, BUFFER_SIZE);

    char *product_code = strstr(buffer, "product=");
    if (product_code == NULL) goto error;

    product_code += 8; // Length of "product="
    char *quantity_str = strchr(product_code, '&');
    if (quantity_str == NULL) goto error;
    *quantity_str = '\0';
    quantity_str++;

    int quantity = atoi(quantity_str + 7); // Skip past "quantity="

    float price_per_unit = get_price(product_code);
    if (price_per_unit < 0) {
        send(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 23\r\n\r\nInvalid product code.\n", 85, 0);
        goto cleanup;
    }

    float total_price = price_per_unit * quantity;
    char response[256];
    snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Length: %zu\r\n\r\nTotal Price: %.2f",
             strlen("Total Price: ") + 7, total_price);
    send(client_socket, response, strlen(response), 0);

cleanup:
    close(client_socket);
    return;

error:
    send(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 23\r\n\r\nInvalid request.\n", 85, 0);
    goto cleanup;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
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
        if ((new_socket = accept(server_fd, NULL, NULL)) < 0) {
            perror("accept");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}