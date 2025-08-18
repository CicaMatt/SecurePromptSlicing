#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void saveFile(char *buffer, int size) {
    FILE *fp = fopen("uploaded_file", "wb");
    if (fp == NULL) {
        perror("Failed to open file for writing");
        return;
    }
    fwrite(buffer, 1, size, fp);
    fclose(fp);
}

int main(int argc, char const *argv[]) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    ssize_t valread;

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

    valread = read(new_socket, buffer, BUFFER_SIZE);
    saveFile(buffer, valread);

    send(new_socket, "File received", 13, 0);
    close(new_socket);
    close(server_fd);

    return 0;
}