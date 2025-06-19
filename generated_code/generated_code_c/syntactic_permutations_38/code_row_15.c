#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "pthread.h"

#define PORT 8080
#define MAX_CONNECTIONS 1000
#define BACKLOG 10
#define IP_ADDRESS "127.0.0.1"
#define LOGIN_PAGE "<html><head><title>Login Page</title></head><body><form action='/login' method='post'><label for='username'>Username:</label><input type='text' id='username' name='username'><br><label for='password'>Password:</label><input type='password' id='password' name='password'><br><input type='submit' value='Submit'></form></body></html>"
#define DASHBOARD "<html><head><title>Dashboard</title></head><body><h1>Welcome to the dashboard!</h1></body></html>"

struct credentials {
    char username[32];
    char password[32];
};

void *connection_handler(void *arg) {
    int client_socket = (int) arg;
    char buffer[4096];
    ssize_t bytes_read, bytes_written;
    
    while((bytes_read = recv(client_socket, buffer, 4096, 0)) > 0) {
        if(strncmp(buffer, "GET /login", 10) == 0) {
            send(client_socket, LOGIN_PAGE, sizeof(LOGIN_PAGE), 0);
        } else if (strncmp(buffer, "POST /login", 12) == 0) {
            struct credentials creds;
            sscanf(buffer + 13, "%s %s", creds.username, creds.password);
            if(strcmp(creds.username, "admin") == 0 && strcmp(creds.password, "password") == 0) {
                send(client_socket, DASHBOARD, sizeof(DASHBOARD), 0);
            } else {
                send(client_socket, "<html><head><title>Login Page</title></head><body><h1>Invalid username or password.</h1></body></html>", 94, 0);
            }
        }
    }
    
    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    socklen_t address_length = sizeof(struct sockaddr_in);
    struct sockaddr_in server_address, client_address;
    
    pthread_t thread_id;
    
    // Create the server socket
    if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    // Set up the server address struct
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);
    
    // Bind the socket to the address and port
    if(bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }
    
    // Listen for incoming connections
    if(listen(server_socket, BACKLOG) < 0) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }
    
    printf("Listening on port %d...\n", PORT);
    
    while(1) {
        // Accept an incoming connection
        if((client_socket = accept(server_socket, (struct sockaddr *) &client_address, &address_length)) < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }
        
        // Handle the connection in a new thread
        pthread_create(&thread_id, NULL, connection_handler, (void *) client_socket);
    }
    
    return 0;
}