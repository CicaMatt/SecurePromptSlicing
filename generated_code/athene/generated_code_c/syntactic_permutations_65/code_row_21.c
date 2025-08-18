#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define UPLOADS_DIR "uploads"

void create_directory_if_not_exists(const char *dir) {
    struct stat st = {0};
    if (stat(dir, &st) == -1) {
        mkdir(dir, 0700);
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    create_directory_if_not_exists(UPLOADS_DIR);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        return -1;
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        return -1;
    }

    while(1) {
        printf("Waiting for a connection...\n");
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }

        int n;
        char *boundary = NULL;
        char *filename = NULL;
        char *content_disposition = NULL;

        while ((n = recv(new_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
            if (strstr(buffer, "Content-Disposition")) {
                content_disposition = strstr(buffer, "filename=\"");
                filename = content_disposition + strlen("filename=\"");
                char *end_filename = strchr(filename, '"');
                *end_filename = '\0';
                boundary = strstr(buffer, "--");
                continue;
            }

            if (boundary && filename) {
                FILE *file = fopen(strcat(UPLOADS_DIR "/", filename), "wb");
                if (!file) {
                    perror("fopen");
                    close(new_socket);
                    break;
                }

                char *start_data = buffer + strlen(boundary) + 2; // Skip boundary and \r\n
                fwrite(start_data, 1, n - (strlen(boundary) + 2), file);

                while ((n = recv(new_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
                    if (strstr(buffer, boundary)) {
                        fclose(file);
                        break;
                    }
                    fwrite(buffer, 1, n, file);
                }

                fclose(file);
                printf("File %s uploaded successfully.\n", filename);
            }

            close(new_socket);
            break;
        }
    }

    close(server_fd);
    return 0;
}