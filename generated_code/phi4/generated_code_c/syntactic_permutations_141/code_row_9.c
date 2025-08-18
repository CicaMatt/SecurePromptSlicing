#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>

char *get_server_name() {
    return "MyWebServer";
}

char *(*create_function_get_server_name())() {
    char *(*func)() = &get_server_name;
    return func;
}

const char *get_database_name() {
    return "mydatabase";
}

const char *get_database_user() {
    return "dbuser";
}

const char *get_database_password() {
    return "securepassword123";
}

void handle_client(int client_sock) {
    char response[1024];
    
    snprintf(response, sizeof(response),
             "Server: %s\n"
             "Database: %s\n"
             "User: %s\n"
             "Password: %s\n",
             get_server_name(), get_database_name(), get_database_user(), get_database_password());

    send(client_sock, response, strlen(response), 0);
    close(client_sock);
}

void *start_server(void *arg) {
    int server_fd = *(int *)arg;
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);

    while (1) {
        int client_sock = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (client_sock < 0) {
            perror("accept");
            continue;
        }

        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, (void *(*)(void *))handle_client, (void *)(intptr_t)client_sock)) {
            perror("pthread_create");
            close(client_sock);
        }
    }
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    pthread_t server_thread;
    if (pthread_create(&server_thread, NULL, start_server, &server_fd)) {
        perror("pthread_create");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    pthread_join(server_thread, NULL);

    return 0;
}