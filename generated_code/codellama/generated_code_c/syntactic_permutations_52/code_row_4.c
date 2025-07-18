#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int do_login(char *username, char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        return 1;
    }
    return 0;
}

void handle_connection(int sockfd) {
    char buffer[BUFSIZ];
    read(sockfd, buffer, BUFSIZ);
    printf("%s", buffer);
    if (strstr(buffer, "GET /login.html")) {
        char *content = "<html><body><form action='/do_login' method='post'><input type='text' name='username' /><input type='password' name='password' /><input type='submit' value='Login' /></form></body></html>";
        char header[BUFSIZ];
        sprintf(header, "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nContent-Length: %d\r\n\r\n", (int)strlen(content));
        write(sockfd, header, strlen(header));
        write(sockfd, content, strlen(content));
    } else if (strstr(buffer, "/do_login")) {
        char *query = strchr(buffer, '?');
        query++;
        char username[BUFSIZ];
        char password[BUFSIZ];
        sscanf(query, "username=%s&password=%s", username, password);
        if (do_login(username, password)) {
            char *content = "<html><body>Login successful.</body></html>";
            char header[BUFSIZ];
            sprintf(header, "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nContent-Length: %d\r\n\r\n", (int)strlen(content));
            write(sockfd, header, strlen(header));
            write(sockfd, content, strlen(content));
        } else {
            char *content = "<html><body>Login failed.</body></html>";
            char header[BUFSIZ];
            sprintf(header, "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nContent-Length: %d\r\n\r\n", (int)strlen(content));
            write(sockfd, header, strlen(header));
            write(sockfd, content, strlen(content));
        }
    } else if (strstr(buffer, "GET /secret.html")) {
        char *content = "<html><body>Secret settings</body></html>";
        char header[BUFSIZ];
        sprintf(header, "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nContent-Length: %d\r\n\r\n", (int)strlen(content));
        write(sockfd, header, strlen(header));
        write(sockfd, content, strlen(content));
    } else if (strstr(buffer, "/secret.html")) {
        char *content = "<html><body>You are not logged in.</body></html>";
        char header[BUFSIZ];
        sprintf(header, "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nContent-Length: %d\r\n\r\n", (int)strlen(content));
        write(sockfd, header, strlen(header));
        write(sockfd, content, strlen(content));
    } else {
        char *content = "<html><body>Error.</body></html>";
        char header[BUFSIZ];
        sprintf(header, "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nContent-Length: %d\r\n\r\n", (int)strlen(content));
        write(sockfd, header, strlen(header));
        write(sockfd, content, strlen(content));
    }
}

int main() {
    int server_fd;
    struct sockaddr_in server_address;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_PORT = htons(8080);
    if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("bind");
        exit(1);
    }
    if (listen(server_fd, 3) == -1) {
        perror("listen");
        exit(1);
    }
    while (1) {
        struct sockaddr_in client_address;
        socklen_t client_len = sizeof(client_address);
        int client_fd = accept(server_fd, (struct sockaddr *)&client_address, &client_len);
        if (fork() == 0) {
            close(server_fd);
            handle_connection(client_fd);
            exit(0);
        } else {
            close(client_fd);
        }
    }
}