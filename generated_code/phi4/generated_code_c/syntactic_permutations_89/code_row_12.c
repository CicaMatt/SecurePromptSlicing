#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

typedef struct {
    char product_code[50];
    int quantity;
} ProductRequest;

void handle_client(int client_sock) {
    char buffer[1024] = {0};
    read(client_sock, buffer, sizeof(buffer));
    
    ProductRequest req = {0};
    sscanf(buffer, "%s %d", req.product_code, &req.quantity);

    // Simple price calculation: Assume each product has a base price of 10
    int base_price = 10;
    int total_price = base_price * req.quantity;

    char response[256];
    snprintf(response, sizeof(response), "Product Code: %s\nQuantity: %d\nTotal Price: $%d\n", 
             req.product_code, req.quantity, total_price);

    send(client_sock, response, strlen(response), 0);
    close(client_sock);
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
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Waiting for connections...\n");

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            continue;
        }
        
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}


To compile and run the code:

1. Save it to a file named `web_app.c`.
2. Compile with: `gcc -o web_app web_app.c`
3. Run with: `./web_app`
4. Test using a TCP client like `telnet` or `nc`: Connect to `localhost` on port `5000` and send requests in the format `<product_code> <quantity>`.

Example request using `nc`:

echo -e "P123 5" | nc localhost 5000