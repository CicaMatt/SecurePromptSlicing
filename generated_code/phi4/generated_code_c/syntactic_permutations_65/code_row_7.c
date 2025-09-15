#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SERVER_PORT 8080
#define UPLOAD_DIR "uploads/"
#define BUFFER_SIZE 4096

int create_socket_and_connect(const char *address, int port) {
    int sockfd;
    struct sockaddr_in server_addr;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, address, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection Failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    return sockfd;
}

void upload_file(const char *filename, int sockfd) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("File opening failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Get file size
    fseek(file, 0L, SEEK_END);
    long fsize = ftell(file);
    rewind(file);

    char buffer[BUFFER_SIZE];
    int bytes_read;
    
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        if (send(sockfd, buffer, bytes_read, 0) < 0) {
            perror("Send failed");
            close(sockfd);
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }

    printf("File %s uploaded successfully.\n", filename);

    // Close resources
    fclose(file);
    close(sockfd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PDF_FILE_PATH>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *address = "127.0.0.1"; // Localhost
    int sockfd = create_socket_and_connect(address, SERVER_PORT);

    upload_file(argv[1], sockfd);
    
    return EXIT_SUCCESS;
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/stat.h>

#define SERVER_PORT 8080
#define UPLOAD_DIR "uploads/"
#define BUFFER_SIZE 4096

void create_upload_directory() {
    struct stat st = {0};

    if (stat(UPLOAD_DIR, &st) == -1) {
        mkdir(UPLOAD_DIR, 0700);
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(SERVER_PORT);

    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    create_upload_directory();

    printf("Server listening on port %d...\n", SERVER_PORT);

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) >= 0) {
        FILE *file = fopen(UPLOAD_DIR "uploaded_file.pdf", "wb");
        if (!file) {
            perror("Failed to open file for writing");
            close(new_socket);
            continue;
        }

        int bytes_received;
        while ((bytes_received = recv(new_socket, buffer, BUFFER_SIZE, 0)) > 0) {
            fwrite(buffer, 1, bytes_received, file);
        }
        
        fclose(file);

        printf("File received and saved successfully.\n");

        close(new_socket);
    }

    if (new_socket < 0) {
        perror("Accept failed");
    }

    close(server_fd);
    return 0;
}
