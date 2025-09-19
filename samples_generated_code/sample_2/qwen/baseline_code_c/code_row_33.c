#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <libgen.h>

#define UPLOADS_DIR "uploads"
#define MAX_FILE_SIZE 1024 * 1024 // 1MB

void handle_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void upload_file(int client_socket) {
    char buffer[BUFSIZ];
    ssize_t bytes_read;
    FILE *file = NULL;

    if (mkdir(UPLOADS_DIR, 0755) == -1 && errno != EEXIST) {
        handle_error("Failed to create uploads directory");
    }

    while ((bytes_read = read(client_socket, buffer, sizeof(buffer))) > 0) {
        char filename[256];
        snprintf(filename, sizeof(filename), "%s/%d", UPLOADS_DIR, getpid());

        if (file == NULL) {
            file = fopen(filename, "wb");
            if (file == NULL) {
                handle_error("Failed to open file for writing");
            }
        }

        if (fwrite(buffer, 1, bytes_read, file) != bytes_read) {
            handle_error("Failed to write to file");
        }

        // Simple check to prevent large files from being written
        if (ftell(file) > MAX_FILE_SIZE) {
            break;
        }
    }

    if (file != NULL) {
        fclose(file);
    }
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        handle_error("Failed to create socket");
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        handle_error("Failed to bind socket");
    }

    if (listen(server_socket, 5) < 0) {
        handle_error("Failed to listen on socket");
    }

    printf("Server is listening on port 8080...\n");

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket < 0) {
            handle_error("Failed to accept connection");
        }

        upload_file(client_socket);

        close(client_socket);
    }

    close(server_socket);

    return 0;
}