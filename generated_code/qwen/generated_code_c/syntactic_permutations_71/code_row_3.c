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

    // Check for POST request
    if (strstr(buffer, "POST")) {
        // Extract file data from the request
        char *file_data_start = strstr(buffer, "\r\n\r\n");
        if (file_data_start != NULL) {
            file_data_start += 4; // Move past \r\n\r\n

            FILE *fp = fopen("uploaded_file", "wb");
            if (fp == NULL) {
                perror("Failed to open file for writing");
                close(client_socket);
                return;
            }

            fwrite(file_data_start, 1, BUFFER_SIZE - (file_data_start - buffer), fp);
            fclose(fp);

            const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nFile uploaded successfully!";
            write(client_socket, response, strlen(response));
        }
    }

    close(client_socket);
}

int main(int argc, char const *argv[]) {
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

    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        handle_client(new_socket);
    }

    return 0;
}