#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024
#define PORT 8080

void login();
void do_login(char *username, char *password);

int main() {
    login();
}

void login() {
    int server_fd;
    struct sockaddr_in server_address;
    int client_fd;
    struct sockaddr_in client_address;

    // create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // address server
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // bind socket
    if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    // listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }

    // accept connection from client
    int addrlen = sizeof(client_address);
    if ((client_fd = accept(server_fd, (struct sockaddr *)&client_address, &addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    // handle connection
    char buffer[BUFFER_SIZE];
    int n;
    n = read(client_fd, buffer, BUFFER_SIZE);
    if (n < 0) {
        perror("Read failed");
        exit(EXIT_FAILURE);
    } else if (!strcmp(buffer, "GET /login HTTP/1.1\r\n")) {
        // send form to user
        char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><title>Login</title></head><body><form method='post' action='/login'><label for='username'>Username: </label><input type='text' name='username' id='username'><br><label for='password'>Password: </label><input type='password' name='password' id='password'><br><input type='submit' value='Login'></form></body></html>";
        if (write(client_fd, response, strlen(response)) < 0) {
            perror("Write failed");
            exit(EXIT_FAILURE);
        }
    } else {
        // do login
        char username[BUFFER_SIZE];
        char password[BUFFER_SIZE];
        sscanf(buffer, "POST /login HTTP/1.1\r\nContent-Length: %d\r\n\r\nusername=%s&password=%s", &n, username, password);
        do_login(username, password);
    }
}

void do_login(char *username, char *password) {
    int server_fd;
    struct sockaddr_in server_address;
    int client_fd;
    struct sockaddr_in client_address;

    // create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // address server
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // bind socket
    if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    // listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }

    // accept connection from client
    int addrlen = sizeof(client_address);
    if ((client_fd = accept(server_fd, (struct sockaddr *)&client_address, &addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    // handle connection
    char buffer[BUFFER_SIZE];
    int n;
    n = read(client_fd, buffer, BUFFER_SIZE);
    if (n < 0) {
        perror("Read failed");
        exit(EXIT_FAILURE);
    } else {
        // check if user is admin
        if (!strcmp(username, "admin") && !strcmp(password, "pass")) {
            char response[] = "HTTP/1.1 302 Found\r\nLocation: /admin_page\r\n\r\n";
            if (write(client_fd, response, strlen(response)) < 0) {
                perror("Write failed");
                exit(EXIT_FAILURE);
            }
        } else {
            // return
            char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><title>Login</title></head><body><p>Incorrect username or password.</p></body></html>";
            if (write(client_fd, response, strlen(response)) < 0) {
                perror("Write failed");
                exit(EXIT_FAILURE);
            }
        }
    }
}