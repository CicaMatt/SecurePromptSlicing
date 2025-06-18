#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8080
#define BUFFER_SIZE 1024
#define DATA_SIZE 32
#define USERNAME "username"
#define PASSWORD "password"
#define SESSION_KEY "session-key"
void info(int client, char *userName);
void login(int client, char *userName, char *password, char *sessionKey);
void logout(char *sessionKey);
void main() {
    int server;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char *data = (char *)malloc(DATA_SIZE);
    if((server = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(server, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d\n", PORT);
    while(1) {
        int client = accept(server, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        printf("Client connected\n");
        char *data = (char *)malloc(DATA_SIZE);
        recv(client, data, DATA_SIZE, 0);
        printf("%s\n", data);
        if (strncmp("/info", data, strlen("/info")) == 0) {
            info(client, USERNAME);
        } else if (strncmp("/login", data, strlen("/login")) == 0) {
            login(client, USERNAME, PASSWORD, SESSION_KEY);
        } else if (strncmp("/logout", data, strlen("/logout")) == 0) {
            logout(SESSION_KEY);
        }
    }
}
void info(int client, char *userName) {
    send(client, userName, DATA_SIZE, 0);
}
void login(int client, char *userName, char *password, char *sessionKey) {
    // TODO: Login the user and set session key
    send(client, "login successful", DATA_SIZE, 0);
}
void logout(char *sessionKey) {
    // TODO: Logout the user
    send(client, "logout successful", DATA_SIZE, 0);
}