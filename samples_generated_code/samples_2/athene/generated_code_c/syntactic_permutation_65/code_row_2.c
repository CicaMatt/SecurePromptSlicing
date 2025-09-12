#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define UPLOADS_DIR "uploads/"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received;
    FILE *file = NULL;

    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        
        if (strstr(buffer, "Content-Disposition: form-data; name=\"file\"; filename=\"") != NULL) {
            char *filename_start = strstr(buffer, "filename=\"") + strlen("filename=\"");
            char *filename_end = strchr(filename_start, '\"');
            int filename_len = filename_end - filename_start;
            char filename[filename_len + 1];
            strncpy(filename, filename_start, filename_len);
            filename[filename_len] = '\0';

            if (file) {
                fclose(file);
            }
            file = fopen(strcat(UPLOADS_DIR, filename), "wb");
        } else if (strstr(buffer, "\r\n\r\n") != NULL && file) {
            fwrite(buffer + 4, 1, bytes_received - 4, file);
        } else if (file) {
            fwrite(buffer, 1, bytes_received, file);
        }

        if (strstr(buffer, "--")) {
            fclose(file);
            break;
        }
    }

    char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nFile uploaded successfully.";
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

    mkdir(UPLOADS_DIR, 0755);

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