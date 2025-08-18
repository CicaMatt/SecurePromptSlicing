#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_REQUEST_SIZE 65536

void handle_client(int client_socket) {
    char request[BUFFER_SIZE];
    ssize_t bytes_read;
    FILE *fp;

    bzero(request, sizeof(request));
    bytes_read = recv(client_socket, request, sizeof(request), 0);
    if (bytes_read > 0 && strstr(request, "POST /upload") != NULL) {
        char boundary[128], header[BUFFER_SIZE];
        sscanf(request, "%*s %*s\r\n%*[^-]--%s", boundary);

        bzero(header, sizeof(header));
        while (recv(client_socket, header, sizeof(header), 0) > 0 && strstr(header, boundary) == NULL) {
            if (strstr(header, "filename=") != NULL) {
                char filename[128];
                sscanf(header, "%*[^']'%*[^']%*[^']'%s", filename);
                fp = fopen(filename, "w");
                bzero(header, sizeof(header));
                continue;
            }
            if (fp && strstr(header, boundary) == NULL) {
                fwrite(header, 1, strlen(header), fp);
                bzero(header, sizeof(header));
            }
        }
        if (fp) fclose(fp);
    }

    char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body>File uploaded successfully.</body></html>";
    send(client_socket, response, strlen(response), 0);
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

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

    printf("Server listening on port %d\n", PORT);

    while(1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}