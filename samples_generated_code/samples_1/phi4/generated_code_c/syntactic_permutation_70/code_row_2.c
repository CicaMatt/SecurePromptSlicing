#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define maximum buffer size for reading data from the client
#define BUFFER_SIZE 1024

void handle_file_upload(int client_socket) {
    char filename[256];
    int received = 0;
    FILE *file;

    // Read the file name sent by the client
    if (recv(client_socket, filename, sizeof(filename), 0) <= 0) {
        perror("Failed to receive filename");
        return;
    }
    
    printf("Received filename: %s\n", filename);

    // Open file for writing in binary mode
    file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    char buffer[BUFFER_SIZE];
    
    // Read the file data sent by the client
    while ((received = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, sizeof(char), received, file);
    }
    
    if (received < 0) {
        perror("Failed to receive file data");
    }

    fclose(file);
}

int main() {
    // Example client socket descriptor
    int client_socket = 0; // Replace with actual socket descriptor

    handle_file_upload(client_socket);

    return 0;
}