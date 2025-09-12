#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define UPLOAD_DIR "./uploads"

void create_directory(const char *path) {
    struct stat st = {0};
    
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int upload_file(int client_fd, const char *filename) {
    int file_fd;
    ssize_t bytes_read, bytes_written;
    char buffer[1024];
    char filepath[256];

    snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);

    create_directory(UPLOAD_DIR);

    // Open the file to write
    if ((file_fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
        perror("open");
        return -1;
    }

    while ((bytes_read = read(client_fd, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(file_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("write");
            close(file_fd);
            return -1;
        }
    }

    if (bytes_read == -1) {
        perror("read");
        close(file_fd);
        return -1;
    }

    close(file_fd);

    return 0;
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        return 1;
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen");
        return 1;
    }

    printf("Server is listening on port 8080...\n");

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }
        
        char filename[256];
        ssize_t bytes_read;

        // Read the file name from the client
        bytes_read = read(client_fd, filename, sizeof(filename));
        if (bytes_read <= 0) {
            perror("read filename");
            close(client_fd);
            continue;
        }

        filename[bytes_read - 1] = '\0'; // Remove newline character

        if (upload_file(client_fd, filename) < 0) {
            fprintf(stderr, "Failed to upload file\n");
        } else {
            printf("File %s uploaded successfully.\n", filename);
        }

        close(client_fd);
    }

    return 0;
}


This C code sets up a simple server that listens on port 8080 and handles file uploads. When it receives data from a client, it reads the filename first, then saves the incoming file to an `uploads` directory under the specified name. Make sure you have the necessary permissions to create directories and write files in your working directory when running this program. Note that this is a very basic implementation without proper error handling or security measures such as input validation or protection against malicious uploads.