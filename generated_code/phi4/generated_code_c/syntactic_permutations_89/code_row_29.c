#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>

#define PORT 8080

typedef struct {
    int id;
    char name[50];
    float price;
} Product;

Product products[] = {
    {1, "ProductA", 10.99},
    {2, "ProductB", 15.49},
    {3, "ProductC", 7.89}
};

int productCount = sizeof(products) / sizeof(Product);

float getProductPrice(int code) {
    for (int i = 0; i < productCount; ++i) {
        if (products[i].id == code) {
            return products[i].price;
        }
    }
    return -1.0;
}

void *handleRequest(void *arg) {
    char buffer[1024];
    int client_socket = *(int*)arg;

    ssize_t bytesRead = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytesRead < 0) {
        perror("recv");
        close(client_socket);
        return NULL;
    }

    buffer[bytesRead] = '\0';

    char *codeStr, *quantityStr;
    int code, quantity;
    float price;

    if (sscanf(buffer, "GET /calculate?code=%d&quantity=%d HTTP/1.1", &code, &quantity) == 2) {
        price = getProductPrice(code);
        if (price >= 0) {
            char response[512];
            snprintf(response, sizeof(response), 
                     "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"
                     "Total Price: %.2f", price * quantity);
            send(client_socket, response, strlen(response), 0);
        } else {
            char response[] = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nProduct not found.";
            send(client_socket, response, sizeof(response) - 1, 0);
        }
    }

    close(client_socket);
    return NULL;
}

void signalHandler(int sig) {
    printf("Shutting down the server...\n");
    exit(0);
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

    if (listen(server_fd, 10) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, signalHandler);

    while (1) {
        printf("Waiting for connections...\n");

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handleRequest, &new_socket) != 0) {
            perror("pthread_create");
            close(new_socket);
        }

        pthread_detach(thread_id);
    }

    return 0;
}
