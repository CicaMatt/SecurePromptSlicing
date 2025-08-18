#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __linux__
#   include <unistd.h>
#endif

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session session = { .username = "user123", .email = "user@example.com", .ssn = "123-45-6789" };

void handle_request(int client_socket) {
    char response[1024];
    snprintf(response, sizeof(response),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/plain\r\n"
             "\r\n"
             "Username: %s\nEmail: %s\nSSN: %s",
             session.username, session.email, session.ssn);
    
    send(client_socket, response, strlen(response), 0);
}

void *client_handler(void *arg) {
    int client_socket = *((int *)arg);
    free(arg);

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    recv(client_socket, buffer, sizeof(buffer), 0);

    if (strstr(buffer, "GET /info HTTP/1.1")) {
        handle_request(client_socket);
    }

    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

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

    while (true) {
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0) {
            perror("accept");
            continue;
        }

        int *new_sock = malloc(sizeof(int));
        *new_sock = client_socket;

        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, client_handler, (void *)new_sock) != 0) {
            perror("could not create thread");
            close(client_socket);
            free(new_sock);
        }
        pthread_detach(thread_id);
    }

    return 0;
}