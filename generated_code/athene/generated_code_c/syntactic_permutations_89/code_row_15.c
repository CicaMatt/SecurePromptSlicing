#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

double calculate_price(double price, int quantity) {
    return price * quantity;
}

void handle_request(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, 1023);
    printf("%s\n", buffer);

    double price = 10.5; // Example fixed price
    int quantity = 0;
    char *quantity_str = strstr(buffer, "quantity=");
    if (quantity_str) {
        quantity_str += strlen("quantity=");
        char *endptr;
        quantity = (int)strtol(quantity_str, &endptr, 10);
        if (*endptr == '&' || *endptr == ' ') {
            double total_price = calculate_price(price, quantity);

            char response[2048];
            snprintf(response, sizeof(response),
                     "HTTP/1.1 200 OK\r\n"
                     "Content-Type: text/html; charset=UTF-8\r\n\r\n"
                     "<html><body>Total Price: %.2f</body></html>", total_price);
            write(client_socket, response, strlen(response));
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

    printf("Listening on port %d...\n", PORT);

    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        handle_request(new_socket);
    }

    return 0;
}