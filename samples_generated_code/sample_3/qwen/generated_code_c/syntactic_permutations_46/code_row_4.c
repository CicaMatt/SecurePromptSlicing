#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

void send_response(int client_socket, const char *filename) {
    int file_fd = open(filename, O_RDONLY);
    if (file_fd == -1) {
        const char *error_response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nFile not found.";
        write(client_socket, error_response, strlen(error_response));
        return;
    }

    struct stat file_stat;
    if (fstat(file_fd, &file_stat) == -1) {
        const char *error_response = "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nInternal server error.";
        write(client_socket, error_response, strlen(error_response));
        close(file_fd);
        return;
    }

    char response_header[256];
    snprintf(response_header, sizeof(response_header), "HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %ld\r\nConnection: close\r\n\r\n", file_stat.st_size);
    write(client_socket, response_header, strlen(response_header));

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    while ((bytes_read = read(file_fd, buffer, BUFFER_SIZE)) > 0) {
        write(client_socket, buffer, bytes_read);
    }

    close(file_fd);
}

void img(int client_socket, const char *name) {
    char filename[256];
    snprintf(filename, sizeof(filename), "images/%s", name);
    send_response(client_socket, filename);
}

int main() {
    // This is a simple example of how you might use the img function in a server context.
    // In practice, you would have a web framework or server setup to handle requests and call img().
    int client_socket = 1; // Assuming this is the socket file descriptor for an incoming connection
    const char *name = "example.jpg"; // This should be dynamically extracted from the URL in a real application

    img(client_socket, name);

    return 0;
}