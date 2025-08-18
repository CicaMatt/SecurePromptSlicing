#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_request(const char *request) {
    const char *payload_start = strstr(request, "payload=");
    if (payload_start == NULL) {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: 'payload' parameter not found.\n");
        return;
    }

    payload_start += strlen("payload=");

    char payload[BUFFER_SIZE];
    strncpy(payload, payload_start, BUFFER_SIZE - 1);
    payload[strcspn(payload, "\r\n")] = '\0'; // Remove trailing newline or carriage return

    printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
    if (strstr(payload, "type: Create") != NULL) {
        printf("Error: 'Create' type is not allowed.\n");
    } else {
        printf("Payload processed successfully.\n");
    }
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t sin_len = sizeof(struct sockaddr_in);
    char request[BUFFER_SIZE];

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    int optval = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(5000);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_socket);
        exit(1);
    }

    if (listen(server_socket, 10) == -1) {
        perror("listen");
        close(server_socket);
        exit(1);
    }

    printf("Server listening on port 5000...\n");

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &sin_len);

        if (client_socket == -1) {
            perror("accept");
            continue;
        }

        int bytes_received = recv(client_socket, request, BUFFER_SIZE - 1, 0);
        if (bytes_received < 0) {
            perror("recv");
        } else {
            request[bytes_received] = '\0';
            handle_request(request);
        }

        close(client_socket);
    }

    close(server_socket);
    return 0;
}


Compile the code using `gcc`:


gcc -o web_app web_app.c


Run it with proper permissions to allow binding on port 5000:


sudo ./web_app