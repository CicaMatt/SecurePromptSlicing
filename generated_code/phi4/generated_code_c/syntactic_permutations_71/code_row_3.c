#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read;
    
    // Read the file name from the client
    memset(buffer, 0, BUFFER_SIZE);
    if ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) <= 0) {
        close(client_socket);
        return;
    }
    
    char filename[256];
    strcpy(filename, "./uploads/");
    strcat(filename, buffer);

    // Create the uploads directory if it doesn't exist
    mkdir("./uploads", 0777);
    
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file");
        close(client_socket);
        return;
    }

    // Read and write the file content
    while ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, sizeof(char), bytes_read, file);
    }
    
    fclose(file);
    printf("File uploaded: %s\n", filename);
    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Could not create socket");
        return 1;
    }

    // Prepare the sockaddr_in structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        return 1;
    }

    // Listen
    listen(server_socket, 3);
    
    printf("Waiting for incoming connections...\n");

    while ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len))) {
        if (fork() == 0) { // Child process
            close(server_socket);
            handle_client(client_socket);
            exit(0);
        }
        close(client_socket); // Parent closes the socket
    }

    if (client_socket < 0) {
        perror("Accept failed");
        return 1;
    }

    return 0;
}


To compile and run this code:

1. Save it to a file, for example `file_server.c`.
2. Compile using: 
   
   gcc -o file_server file_server.c
   
3. Run the server with:
   
   ./file_server
   

The client can connect via any socket programming method (e.g., using Python's `socket` library) to send a filename followed by the file data in chunks.