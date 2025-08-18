#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUFFER_SIZE 4096
#define UPLOADS_DIR "uploads"

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    int n;
    FILE *fp;

    while ((n = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[n] = '\0';
        if (strstr(buffer, "Content-Disposition: form-data; name=\"file\"; filename=\"") != NULL) {
            char filename[BUFFER_SIZE];
            sscanf(buffer, "Content-Disposition: form-data; name=\"file\"; filename=\"%[^\"]", filename);
            mkdir(UPLOADS_DIR, 0755);
            snprintf(buffer, BUFFER_SIZE, "%s/%s", UPLOADS_DIR, filename);
            fp = fopen(buffer, "wb");
            if (fp == NULL) {
                perror("Failed to open file for writing");
                return;
            }
            while ((n = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
                if (strstr(buffer, "--") != NULL) break; // End of file
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
        perror("Socket creation failed");
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return -1;
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        return -1;
    }

    while (1) {
        printf("Waiting for a connection...\n");
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }
        handle_request(new_socket);
    }

    return 0;
}