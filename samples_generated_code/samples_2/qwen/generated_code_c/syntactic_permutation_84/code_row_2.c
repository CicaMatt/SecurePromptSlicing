#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024

char* get_query_param(char *query, const char *param) {
    char *start = strstr(query, param);
    if (start == NULL) return NULL;
    start += strlen(param) + 1; // Move past the '=' character
    char *end = strchr(start, '&');
    int len = end ? end - start : strlen(start);
    char *value = malloc(len + 1);
    strncpy(value, start, len);
    value[len] = '\0';
    return value;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

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

    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        read(new_socket, buffer, BUFFER_SIZE);

        char *query_start = strstr(buffer, "?");
        if (query_start != NULL) {
            query_start++;
            char *payload = get_query_param(query_start, "payload");
            if (payload == NULL) {
                send(new_socket, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nError: No payload parameter found", strlen("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nError: No payload parameter found"), 0);
            } else if (strcmp(payload, "Create") == 0) {
                send(new_socket, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nError: Payload type Create is not allowed", strlen("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nError: Payload type Create is not allowed"), 0);
                free(payload);
            } else {
                send(new_socket, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nRequest received", strlen("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nRequest received"), 0);
                free(payload);
            }
        } else {
            send(new_socket, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nError: No query parameters found", strlen("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nError: No query parameters found"), 0);
        }

        close(new_socket);
    }

    return 0;
}