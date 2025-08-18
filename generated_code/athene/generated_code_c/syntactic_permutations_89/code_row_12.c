#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

float calculate_price(const char *product_code, int quantity) {
    if (strcmp(product_code, "A123") == 0) return quantity * 10.99;
    else if (strcmp(product_code, "B456") == 0) return quantity * 5.75;
    else if (strcmp(product_code, "C789") == 0) return quantity * 20.00;
    return -1; // Invalid product code
}

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, 1023);
    printf("Received: %s\n", buffer);

    const char *product_code = "A123"; // Example product code
    int quantity = 5; // Example quantity

    float price = calculate_price(product_code, quantity);
    if (price < 0) {
        char response[] = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid Product Code";
        send(client_socket, response, strlen(response), 0);
    } else {
        char price_str[20];
        sprintf(price_str, "%.2f", price);

        char response[512];
        snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nPrice for %s x %d: $%s", product_code, quantity, price_str);
        send(client_socket, response, strlen(response), 0);
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

    printf("Listening on port %d...\n", PORT);

    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}