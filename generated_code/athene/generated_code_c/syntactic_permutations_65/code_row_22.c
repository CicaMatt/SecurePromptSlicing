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
    char buffer[BUFFER_SIZE];
    int bytes_received;
    FILE *file = NULL;

    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';

        if (strstr(buffer, "Content-Disposition: form-data; name=\"pdf\"; filename=\"") != NULL) {
            char *filename_start = strstr(buffer, "\"filename=\"") + strlen("\"filename=\"");
            char *filename_end = strchr(filename_start, '\"');
            int filename_length = filename_end - filename_start;

            if (filename_length > 0) {
                char filename[256];
                strncpy(filename, filename_start, filename_length);
                filename[filename_length] = '\0';

                char filepath[256];
                snprintf(filepath, sizeof(filepath), "%s%s", UPLOAD_DIR, filename);

                file = fopen(filepath, "wb");
                if (file == NULL) {
                    close(client_socket);
                    return;
                }
            }
        }

        if (file != NULL && strstr(buffer, "\r\n\r\n") != NULL) {
            char *start_data = strstr(buffer, "\r\n\r\n") + 4;
            fwrite(start_data, 1, bytes_received - (start_data - buffer), file);
        } else if (file != NULL) {
            fwrite(buffer, 1, bytes_received, file);
        }

        if (strstr(buffer, "--boundary--\r\n") != NULL) {
            break;
        }
    }

    if (file != NULL) {
        fclose(file);
    }

    const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n";
    send(client_socket, response, strlen(response), 0);
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    mkdir(UPLOAD_DIR, 0755);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}