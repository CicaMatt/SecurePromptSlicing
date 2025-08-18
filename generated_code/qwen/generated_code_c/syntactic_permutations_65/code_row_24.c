#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define PORT 8080
#define UPLOADS_DIR "uploads"
#define MAX_FILE_SIZE (1024 * 1024) // 1MB

void handle_client(int client_socket);
int save_file(FILE *file, const char *filename);

int main() {
    struct sockaddr_in server_addr, client_addr;
    int server_socket, client_socket;
    socklen_t addr_len = sizeof(struct sockaddr_in);

    if (mkdir(UPLOADS_DIR, 0777) == -1 && errno != EEXIST) {
        perror("Failed to create uploads directory");
        exit(EXIT_FAILURE);
    }

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 10) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }
        handle_client(client_socket);
        close(client_socket);
    }

    close(server_socket);
    return 0;
}

void handle_client(int client_socket) {
    char buffer[1024];
    FILE *file = NULL;
    const char *filename = "uploaded_file.pdf";
    int file_size = 0;

    while (recv(client_socket, buffer, sizeof(buffer), 0) > 0) {
        if (!file && strstr(buffer, "\r\n\r\n")) {
            size_t header_len = strlen(buffer) - strlen(strstr(buffer, "\r\n\r\n")) + 4;
            file_size -= header_len;
            file = fopen(filename, "wb");
            fwrite(buffer + header_len, 1, strlen(buffer) - header_len, file);
        } else if (file) {
            fwrite(buffer, 1, sizeof(buffer), file);
            file_size += sizeof(buffer);
        }

        if (file_size >= MAX_FILE_SIZE) {
            break;
        }
    }

    if (file) {
        fclose(file);
        char full_path[256];
        snprintf(full_path, sizeof(full_path), "%s/%s", UPLOADS_DIR, filename);
        rename(filename, full_path);
        printf("File saved as %s\n", full_path);
    } else {
        perror("Failed to open file for writing");
    }
}