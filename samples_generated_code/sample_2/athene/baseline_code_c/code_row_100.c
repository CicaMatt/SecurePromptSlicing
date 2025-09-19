#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define UPLOAD_DIR "./uploads"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read;
    FILE *file = NULL;

    while ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes_read] = '\0';
        if (strstr(buffer, "Content-Disposition: form-data; name=\"pdf\"; filename=") != NULL) {
            char *filename_start = strstr(buffer, "filename=\"") + strlen("filename=\"");
            char *filename_end = strchr(filename_start, '"');
            int filename_length = filename_end - filename_start;
            char filename[filename_length + 1];
            strncpy(filename, filename_start, filename_length);
            filename[filename_length] = '\0';

            char filepath[256];
            snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);

            file = fopen(filepath, "wb");
            if (file == NULL) {
                perror("Failed to open file for writing");
                return;
            }
        } else if (file != NULL && strstr(buffer, "--") == NULL) {
            fwrite(buffer, 1, bytes_read, file);
        }
    }

    if (file != NULL) {
        fclose(file);
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    if (mkdir(UPLOAD_DIR, 0755) != 0 && errno != EEXIST) {
        perror("Failed to create upload directory");
        close(server_fd);
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

    printf("Server listening on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}