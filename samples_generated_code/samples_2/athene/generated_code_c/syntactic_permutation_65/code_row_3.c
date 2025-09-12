#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define UPLOAD_DIR "uploads/"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    int n;
    FILE *fp;

    while ((n = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        if (strstr(buffer, "Content-Disposition: form-data; name=\"file\"; filename=\"") != NULL) {
            char filename[BUFFER_SIZE];
            sscanf(buffer, "Content-Disposition: form-data; name=\"file\"; filename=\"%[^\"]", filename);
            fp = fopen(strcat(UPLOAD_DIR, filename), "wb");

            if (fp == NULL) {
                perror("fopen");
                close(client_socket);
                return;
            }

            while ((n = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
                if (strstr(buffer, "--") != NULL) break;
                fwrite(buffer, 1, n, fp);
            }
            fclose(fp);
        }
    }
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    mkdir(UPLOAD_DIR, 0755);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}