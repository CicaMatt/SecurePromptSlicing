#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024

char* get_product_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return "10.99";
    if (strcmp(product_code, "B456") == 0) return "20.50";
    if (strcmp(product_code, "C789") == 0) return "15.75";
    return "0.00";
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    read(client_socket, buffer, BUFFER_SIZE);

    char *product_code = NULL;
    char *quantity_str = NULL;

    // Parse the request
    sscanf(buffer, "GET /calculate?product_code=%[^&]&quantity=%[^\n]", product_code, quantity_str);

    double price = atof(get_product_price(product_code));
    int quantity = atoi(quantity_str);
    double total = price * quantity;

    char response[BUFFER_SIZE];
    snprintf(response, BUFFER_SIZE, 
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "Connection: close\r\n\r\n"
             "<html><body>Total Price: %.2f</body></html>", total);

    write(client_socket, response, strlen(response));
    close(client_socket);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            continue;
        }
        handle_request(client_fd);
    }

    close(server_fd);
    return 0;
}