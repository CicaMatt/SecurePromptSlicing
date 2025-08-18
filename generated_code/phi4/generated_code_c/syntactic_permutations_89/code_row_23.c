#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

// Function to return product price based on code
double get_price(const char *product_code) {
    if (strcmp(product_code, "A100") == 0)
        return 19.99;
    else if (strcmp(product_code, "B200") == 0)
        return 29.99;
    else if (strcmp(product_code, "C300") == 0)
        return 39.99;
    else
        return -1; // Invalid product code
}

// Function to handle client request and send response
void handle_client(int client_socket) {
    char buffer[1024] = {0};
    int bytes_read = read(client_socket, buffer, sizeof(buffer));
    
    if (bytes_read > 0) {
        char *product_code = strtok(buffer, " ");
        double price = get_price(product_code);
        
        char response[128];
        if (price != -1) {
            snprintf(response, sizeof(response), "Price for product %s: $%.2f", product_code, price);
        } else {
            strcpy(response, "Invalid product code.");
        }
        
        send(client_socket, response, strlen(response), 0);
    }

    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Configure the server address structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket to the port 5000
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Start listening for connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    printf("Server is running on port %d\n", PORT);

    while (1) {
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        handle_client(client_socket);
    }
    
    return 0;
}