#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "sqlite3.h"
#include <openssl/sha.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_sock) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = recv(client_sock, buffer, sizeof(buffer), 0);
    if (bytes_read <= 0) return;

    printf("Received: %s\n", buffer);

    // Extract username and password
    char *username = strtok(buffer, ",");
    char *password = strtok(NULL, ",");

    if (username && password) {
        unsigned char hashed_password[SHA256_DIGEST_LENGTH];
        SHA256((unsigned char*)password, strlen(password), hashed_password);
        
        char query[BUFFER_SIZE];
        snprintf(query, sizeof(query),
                 "INSERT INTO users(username, password) VALUES('%s', '%s');",
                 username,
                 (char *)hashed_password); // This needs to be converted back to a string

        sqlite3 *db;
        sqlite3_stmt *stmt;

        if (sqlite3_open("users.db", &db)) {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            return;
        }

        if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) {
            fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return;
        }

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
        } else {
            printf("User registered successfully.\n");
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }
}

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Cannot create socket");
        return -1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding failed");
        close(server_sock);
        return -1;
    }

    if (listen(server_sock, 5) < 0) {
        perror("Listen failed");
        close(server_sock);
        return -1;
    }

    printf("Server listening on port %d\n", PORT);

    while ((client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_len))) {
        if (fork() == 0) { // Child process
            close(server_sock);
            handle_client(client_sock);
            close(client_sock);
            exit(0);
        }
        close(client_sock); // Parent closes the connected socket
    }

    close(server_sock);
    return 0;
}