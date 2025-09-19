#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

void create_directory(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int main() {
    const char *uploads_dir = "./uploads";
    create_directory(uploads_dir);

    int client_fd;
    char buffer[1024];
    
    printf("Enter client file descriptor: ");
    scanf("%d", &client_fd);

    while (1) {
        ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) break;

        const char *content_disposition = "Content-Disposition: form-data; name=\"file\"; filename=\"";
        const char *end_of_header = "\r\n\r\n";
        char file_name[256] = {0};
        
        // Extracting the filename from Content-Disposition header
        if (strstr(buffer, content_disposition) != NULL) {
            char *filename_start = strstr(buffer, content_disposition) + strlen(content_disposition);
            char *filename_end = strstr(filename_start, "\"");
            strncpy(file_name, filename_start, filename_end - filename_start);

            // Reading file data
            memset(buffer, 0, sizeof(buffer));
            while (strstr(buffer, end_of_header) == NULL) {
                bytes_received = recv(client_fd, buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), 0);
                if (bytes_received <= 0) break;
            }

            // Writing to file
            char full_path[512];
            snprintf(full_path, sizeof(full_path), "%s/%s", uploads_dir, file_name);

            int file_fd = open(full_path, O_WRONLY | O_CREAT, 0644);
            if (file_fd < 0) {
                perror("Error opening file");
                continue;
            }

            write(file_fd, strstr(buffer, end_of_header) + strlen(end_of_header), bytes_received - (strlen(strstr(buffer, end_of_header)) + strlen(end_of_header)));
            close(file_fd);

            printf("File %s uploaded successfully.\n", file_name);
        }
    }

    return 0;
}