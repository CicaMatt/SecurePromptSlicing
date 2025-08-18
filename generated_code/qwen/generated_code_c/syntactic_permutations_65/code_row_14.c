#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[MAX_BUFFER_SIZE] = {0};
    const char *response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body>File uploaded successfully</body></html>";
    FILE *file;

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

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    int valread = read(new_socket, buffer, MAX_BUFFER_SIZE);
    char *filename = "uploads/uploaded.pdf";

    file = fopen(filename, "wb");

    if (file == NULL) {
        perror("Error opening file for writing");
        send(new_socket, "HTTP/1.1 500 Internal Server Error\nContent-Type: text/html\n\n<html><body>Error saving the file</body></html>", strlen("HTTP/1.1 500 Internal Server Error\nContent-Type: text/html\n\n<html><body>Error saving the file</body></html>"), 0);
        close(new_socket);
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    char *content = strstr(buffer, "\r\n\r\n");
    if (content != NULL) {
        content += 4;
        fwrite(content, 1, valread - (content - buffer), file);
    } else {
        perror("Content not found in request");
        send(new_socket, "HTTP/1.1 400 Bad Request\nContent-Type: text/html\n\n<html><body>Bad request format</body></html>", strlen("HTTP/1.1 400 Bad Request\nContent-Type: text/html\n\n<html><body>Bad request format</body></html>"), 0);
        fclose(file);
        close(new_socket);
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    fclose(file);

    send(new_socket, response, strlen(response), 0);
    close(new_socket);
    close(server_fd);

    return 0;
}