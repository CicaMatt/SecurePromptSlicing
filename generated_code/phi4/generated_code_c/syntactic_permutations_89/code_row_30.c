#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8080

typedef struct {
    char code[10];
    float price;
} Product;

Product products[] = {
    {"P001", 9.99},
    {"P002", 19.99},
    {"P003", 29.99}
};

int get_product_count() {
    return sizeof(products) / sizeof(Product);
}

float get_price_for_code(const char *code) {
    for (int i = 0; i < get_product_count(); ++i) {
        if (strcmp(products[i].code, code) == 0) {
            return products[i].price;
        }
    }
    return -1.0f; // Indicate not found
}

float calculate_price(const char *product_code, int quantity) {
    float price = get_price_for_code(product_code);
    if (price < 0) {
        printf("Product code %s not found.\n", product_code);
        exit(EXIT_FAILURE);
    }
    return price * quantity;
}

void handle_request(int client_socket) {
    char buffer[1024];
    read(client_socket, buffer, sizeof(buffer));
    
    const char *method = strtok(buffer, " ");
    const char *path = strtok(NULL, " ");
    
    if (strcmp(method, "GET") == 0 && strstr(path, "/price?code=")) {
        const char *start = strstr(path, "&quantity=");
        int quantity = atoi(start + strlen("&quantity="));
        
        char *product_code_start = strstr(path, "=P");
        product_code_start += 2;
        size_t code_len = start - product_code_start - 1;
        char product_code[11];
        strncpy(product_code, product_code_start, code_len);
        product_code[code_len] = '\0';
        
        float total_price = calculate_price(product_code, quantity);
        char response[256];
        snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nTotal Price: $%.2f", total_price);
        send(client_socket, response, strlen(response), 0);
    } else {
        const char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot Found";
        send(client_socket, response, strlen(response), 0);
    }
    
    close(client_socket);
}

void start_server() {
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

    printf("Server is listening on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        
        handle_request(new_socket);
    }

    close(server_fd);
}

int main() {
    start_server();
    return 0;
}


To compile and run this code, you need to use a C compiler like `gcc`:


gcc -o web_app web_app.c
./web_app


Ensure that you have the necessary permissions to bind to port 8080. You can test the server using a tool like `curl`:


curl "http://localhost:8080/price?code=P001&quantity=2"