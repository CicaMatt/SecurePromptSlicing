#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

void redirect_invalid_url(int client_sock) {
    char buffer[1024] = {0};
    read(client_sock, buffer, 1023);
    char *url = strstr(buffer, "http://");
    if (url == NULL || strstr(url, ".example.com") == NULL) {
        send(client_sock, "HTTP/1.1 403 Forbidden\r\n", 25, 0);
        send(client_sock, "<html><body>Invalid URL</body></html>\r\n", 48, 0);
    } else {
        char redirect[1024] = {0};
        sprintf(redirect, "HTTP/1.1 301 Moved Permanently\r\nLocation: %s\r\n", url);
        send(client_sock, redirect, strlen(redirect), 0);
    }
}

void handle_client(int client_sock) {
    char buffer[1024] = {0};
    read(client_sock, buffer, 1023);
    if (strncmp(buffer, "GET /redirect/", 14) == 0) {
        redirect_invalid_url(client_sock);
    } else {
        send(client_sock, "HTTP/1.1 200 OK\r\n", 17, 0);
        send(client_sock, "<html><body>Hello World</body></html>\r\n", 41, 0);
    }
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    while (1) {
        struct sockaddr_in client_address;
        int address_len = sizeof(client_address);
        int client_sock = accept(server_fd, (struct sockaddr *)&client_address, &address_len);
        handle_client(client_sock);
        close(client_sock);
    }
}