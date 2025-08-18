#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define UPLOAD_DIR "./uploads"

void upload_file(int client_socket) {
    char buffer[BUFFER_SIZE];
    FILE *file;
    int bytes_read;

    while ((bytes_read = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        if (strncmp(buffer, "POST", 4) == 0) {
            // Assuming the file name is passed in the request
            char filename[BUFFER_SIZE];
            sscanf(buffer, "%*s %*s %*s Content-Disposition: form-data; name=\"file\"; filename=\"%[^\"]\"", filename);
            char filepath[256];
            snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);

            file = fopen(filepath, "wb");
            if (!file) {
                send(client_socket, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 29\r\n\r\nFailed to create file on server.", 85, 0);
                return;
            }

            // Read the content of the file
            while ((bytes_read = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
                if (strncmp(buffer, "--", 2) == 0) break; // End of file data
                fwrite(buffer, 1, bytes_read, file);
            }

            fclose(file);
            send(client_socket, "HTTP/1.1 200 OK\r\nContent-Length: 34\r\n\r\nFile uploaded successfully.", 65, 0);
        }
    }
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);

    if (mkdir(UPLOAD_DIR, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1 && errno != EEXIST) {
        perror("Failed to create uploads directory");
        exit(EXIT_FAILURE);
    }

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (client_fd < 0) {
            perror("Accept failed");
            continue;
        }

        upload_file(client_fd);
        close(client_fd);
    }

    close(server_fd);
    return 0;
}