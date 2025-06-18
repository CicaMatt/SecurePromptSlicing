#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void handle_connection(int socket, struct sockaddr_in client);
unsigned int calculate_price(char product_code[4], unsigned int quantity);

int main() {
    // Create a new TCP socket
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    // Configure the server address
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(5000);

    // Bind the socket to the address and port
    bind(listenfd, (struct sockaddr *)&server, sizeof(server));

    // Listen for incoming connections
    listen(listenfd, 10);

    printf("Listening on port %d\n", server.sin_port);

    while (1) {
        int client;

        // Accept an incoming connection request
        struct sockaddr_in client_addr;
        socklen_t client_addr_size = sizeof(client_addr);
        client = accept(listenfd, (struct sockaddr *)&client_addr, &client_addr_size);

        // Handle the connection in a new thread
        handle_connection(client, client_addr);
    }
}

void handle_connection(int socket, struct sockaddr_in client) {
    char buffer[1024];

    // Receive data from the client
    int bytes_received = recv(socket, buffer, 1024, 0);

    if (bytes_received > 0) {
        // Process the request
        char product_code[4];
        unsigned int quantity;

        sscanf(buffer, "%3s %u", product_code, &quantity);

        unsigned int price = calculate_price(product_code, quantity);

        // Send the response back to the client
        char response[1024];
        sprintf(response, "Price: %d\n", price);

        send(socket, response, strlen(response), 0);
    }
}

unsigned int calculate_price(char product_code[4], unsigned int quantity) {
    // TODO: Implement the pricing logic
    return 1;
}