#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080

void login() {
    printf("Login Function\n");
}

void do_login(char *username, char *password) {
    int client_socket;
    struct sockaddr_in server_address;
    char post_request[512];

    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return;
    }

    memset(&server_address, '0', sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return;
    }

    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection Failed");
        return;
    }

    snprintf(post_request, sizeof(post_request),
             "POST /login HTTP/1.1\r\n"
             "Host: localhost:%d\r\n"
             "Content-Type: application/x-www-form-urlencoded\r\n"
             "Content-Length: %zu\r\n"
             "\r\n"
             "username=%s&password=%s",
             PORT, strlen("username=") + strlen(username) + strlen("&password=") + strlen(password), username, password);

    send(client_socket, post_request, strlen(post_request), 0);
    close(client_socket);
}

void index() {
    printf("Index Function\n");
}

void user_page() {
    printf("User Page Function\n");
}

void admin_page() {
    printf("Admin Page Function\n");
}

int main(int argc, char const *argv[]) {
    login();
    do_login("admin", "password123");
    index();
    user_page();
    admin_page();
    return 0;
}