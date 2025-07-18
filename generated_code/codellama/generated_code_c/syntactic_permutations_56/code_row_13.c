#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#define MAX_CONNECTIONS 1024
#define BUFFER_SIZE 2048
#define PORT 9001
typedef struct {
    char *old_email;
    char *new_email;
    char *password;
} email_t;
void die(const char *s) {
    perror(s);
    exit(EXIT_FAILURE);
}
void logout(int client_sock) {
    close(client_sock);
}
void login(int client_sock, email_t *email) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    if (read(client_sock, buffer, BUFFER_SIZE - 1) <= 0) {
        die("Failed to read from client");
    }
    printf("%s", buffer);
}
void change_email(int client_sock, email_t *email) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    if (read(client_sock, buffer, BUFFER_SIZE - 1) <= 0) {
        die("Failed to read from client");
    }
    char *new_email = strtok(buffer, ":");
    char *password = strtok(NULL, ":");
    if (strcmp(email->password, password) != 0) {
        printf("Invalid password\n");
        logout(client_sock);
    } else if (strcmp(email->old_email, new_email) == 0) {
        printf("Email is same as old email\n");
        logout(client_sock);
    } else {
        free(email->new_email);
        email->new_email = malloc((strlen(new_email) + 1) * sizeof(char));
        strcpy(email->new_email, new_email);
        printf("Email changed successfully\n");
        logout(client_sock);
    }
}
void handle_client(int client_sock) {
    char buffer[BUFFER_SIZE];
    email_t *email = malloc(sizeof(email_t));
    email->old_email = "";
    email->new_email = "";
    email->password = "";
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        if (read(client_sock, buffer, BUFFER_SIZE - 1) <= 0) {
            break;
        }
        char *command = strtok(buffer, ":");
        if (strcmp(command, "login") == 0) {
            login(client_sock, email);
        } else if (strcmp(command, "change_email") == 0) {
            change_email(client_sock, email);
        } else {
            printf("Invalid command\n");
            logout(client_sock);
        }
    }
}
void *handle_clients(void *arg) {
    int client_sock = (int)arg;
    handle_client(client_sock);
    return NULL;
}
int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    pthread_t thread;
    if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        die("Failed to create server socket");
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        die("Failed to bind server socket");
    }
    listen(server_sock, MAX_CONNECTIONS);
    while (1) {
        int addrlen = sizeof(client_addr);
        if ((client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addrlen)) < 0) {
            die("Failed to create client socket");
        }
        pthread_create(&thread, NULL, handle_clients, (void *)client_sock);
    }
}