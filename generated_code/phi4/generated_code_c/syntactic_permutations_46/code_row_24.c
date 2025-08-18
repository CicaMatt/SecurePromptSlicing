#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080

void send_file_to_client(int client_socket, const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        const char *response = "HTTP/1.1 404 Not Found\r\nContent-Length: 13\r\n\r\nFile not found";
        send(client_socket, response, strlen(response), 0);
        return;
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = (char *)malloc(fsize + 1);
    fread(data, 1, fsize, file);
    fclose(file);

    char header[1024];
    snprintf(header, sizeof(header), "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\n\r\n", fsize);
    send(client_socket, header, strlen(header), 0);
    send(client_socket, data, fsize, 0);

    free(data);
}

void img_function(int client_socket, const char *path) {
    if (strstr(path, "/img/") != path) return;

    const char *file_path = "images/";
    file_path += strlen("/img/");

    send_file_to_client(client_socket, file_path);
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if (server_fd == 0) {
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

    while (1) {
        int client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_socket < 0) {
            perror("accept");
            continue;
        }

        char buffer[1024] = {0};
        read(client_socket, buffer, 1024);

        const char *method = strtok(buffer, " ");
        const char *path = strtok(NULL, " ");

        if (strcmp(method, "GET") == 0) {
            img_function(client_socket, path);
        }

        close(client_socket);
    }
    
    return 0;
}