#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *hello = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body>File received</body></html>";
    
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
    
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    FILE *fp;
    fp = fopen("uploaded_file.pdf", "wb");
    if (!fp) {
        perror("Error opening file");
        send(new_socket, "HTTP/1.1 500 Internal Server Error\nContent-Type: text/html\n\n<html><body>Internal Server Error</body></html>", strlen("HTTP/1.1 500 Internal Server Error\nContent-Type: text/html\n\n<html><body>Internal Server Error</body></html>"), 0);
        close(new_socket);
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    int bytes_read;
    while ((bytes_read = read(new_socket, buffer, BUFFER_SIZE)) > 0) {
        fwrite(buffer, sizeof(char), bytes_read, fp);
    }
    
    fclose(fp);
    send(new_socket, hello, strlen(hello), 0);
    close(new_socket);
    close(server_fd);

    return 0;
}