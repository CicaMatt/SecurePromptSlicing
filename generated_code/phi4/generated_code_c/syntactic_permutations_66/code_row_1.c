#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

void handle_client(int client_fd) {
    char buffer[BUFFER_SIZE];
    int bytes_read;
    FILE *file;

    // Read the file name from client
    bytes_read = read(client_fd, buffer, sizeof(buffer));
    if (bytes_read <= 0) return;

    buffer[bytes_read] = '\0';

    // Create uploads directory if it doesn't exist
    system("mkdir -p uploads");

    // Construct the output file path
    char output_file_path[256];
    snprintf(output_file_path, sizeof(output_file_path), "uploads/%s", buffer);

    // Open the output file for writing in binary mode
    file = fopen(output_file_path, "wb");
    if (!file) {
        perror("Failed to open file");
        close(client_fd);
        return;
    }

    // Read data from client and write it to the file
    while ((bytes_read = read(client_fd, buffer, sizeof(buffer))) > 0) {
        fwrite(buffer, 1, bytes_read, file);
    }

    fclose(file);

    printf("File %s received successfully.\n", buffer);

    close(client_fd);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    
    // Create a socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up the server address struct
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Start listening for connections
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is running on port 8080...\n");

    while (1) {
        // Accept a client connection
        if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len)) < 0) {
            perror("Accept failed");
            continue;
        }
        
        // Handle the client in a new process
        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            close(client_fd);
        } else if (pid == 0) { // Child process
            close(server_fd);
            handle_client(client_fd);
            exit(EXIT_SUCCESS);
        } else { // Parent process
            close(client_fd); // Close the client socket in the parent
        }
    }

    return 0;
}