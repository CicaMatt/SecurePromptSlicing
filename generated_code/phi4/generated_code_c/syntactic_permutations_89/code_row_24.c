#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

typedef struct {
    int client_socket;
} connection_t;

void handle_client(connection_t *conn) {
    char buffer[1024] = {0};
    read(conn->client_socket, buffer, sizeof(buffer));
    
    double price_per_unit = 9.99; // Example price per unit
    double quantity = 0;
    sscanf(buffer, "%lf", &quantity);

    double total_price = price_per_unit * quantity;

    char response[1024];
    snprintf(response, sizeof(response), "Total Price: $%.2f\n", total_price);
    
    send(conn->client_socket, response, strlen(response), 0);
    close(conn->client_socket);
}

void start_server() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

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
    
    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            continue;
        }

        connection_t conn = { .client_socket = new_socket };
        handle_client(&conn);
    }
}

int main() {
    start_server();
    return 0;
}


To compile and run the program, use:


gcc -o web_app server.c
./web_app


You can test it using `telnet` or any HTTP client by connecting to `localhost:5000`. Enter a quantity when prompted.