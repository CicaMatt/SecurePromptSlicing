#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8080

typedef struct {
    char method[8];
    char path[256];
} Request;

void handle_request(Request *req) {
    if (strcmp(req->method, "GET") == 0 && strcmp(req->path, "/hello") == 0) {
        printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, World!\r\n");
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot Found\r\n");
    }
}

void start_server() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t sin_len = sizeof(client_addr);

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Socket bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 10) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &sin_len)) < 0) {
            perror("Accept failed");
            continue;
        }

        char buffer[1024];
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';
            Request req;
            sscanf(buffer, "%s %s", req.method, req.path);
            handle_request(&req);
        }

        close(client_socket);
    }
}

int main() {
    start_server();
    return 0;
}


To compile and run this code, you'll need a C compiler like `gcc`:


gcc -o webapp webapp.c
./webapp


This basic server listens on port 8080 and responds to `GET /hello` requests with "Hello, World!" and returns a 404 for other paths.