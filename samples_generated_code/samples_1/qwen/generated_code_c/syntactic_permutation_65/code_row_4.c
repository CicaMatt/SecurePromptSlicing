#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    int valread = read(client_socket, buffer, BUFFER_SIZE);
    if (valread <= 0) {
        close(client_socket);
        return;
    }

    // Simple check to see if the request is a POST and for PDF upload
    if (strstr(buffer, "POST") && strstr(buffer, "Content-Type: application/pdf")) {
        FILE *file = fopen("uploads/uploaded.pdf", "wb");
        if (!file) {
            send(client_socket, "HTTP/1.1 500 Internal Server Error\r\n\r\n", 36, 0);
            close(client_socket);
            return;
        }

        char *body_start = strstr(buffer, "\r\n\r\n") + 4;
        fwrite(body_start, 1, valread - (body_start - buffer), file);
        fclose(file);

        send(client_socket, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nFile uploaded successfully", 67, 0);
    } else {
        send(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid request", 59, 0);
    }

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

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is running on port %d\n", PORT);

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))>=0) {
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}