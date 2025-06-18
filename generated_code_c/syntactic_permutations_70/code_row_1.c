// header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

// macro definitions
#define BUFFER_SIZE 1024
#define UPLOADS_DIR "./uploads"
#define MAX_FILENAME_LEN 50

// function prototypes
void upload_file(int client_socket);
int create_directory(const char* dirname);
int write_to_file(const char* filename, const char* data);

// main program
int main(int argc, char* argv[]) {
    // check if the uploads directory exists and create it if not
    if (create_directory(UPLOADS_DIR) == -1) {
        printf("Error creating directory\n");
        return 0;
    }

    // start listening for incoming connections on port 8080
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        printf("Error creating socket\n");
        return 0;
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        printf("Error binding socket\n");
        return 0;
    }

    listen(server_socket, 3);

    while (1) {
        struct sockaddr_in client_address;
        socklen_t sin_size = sizeof(client_address);
        int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &sin_size);

        upload_file(client_socket);
    }
}

// function definitions
void upload_file(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received = 0;
    int total_bytes_received = 0;
    int file_size = 0;
    FILE* fp;

    // read the file size from the client socket
    recv(client_socket, buffer, BUFFER_SIZE, 0);
    sscanf(buffer, "%d", &file_size);

    // create a filename for the uploaded file
    char filename[MAX_FILENAME_LEN];
    sprintf(filename, "upload_%d.txt", time(NULL));

    // open the file and write the received data to it
    fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    while (total_bytes_received < file_size) {
        bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        fwrite(buffer, sizeof(char), bytes_received, fp);
        total_bytes_received += bytes_received;
    }

    fclose(fp);
}

int create_directory(const char* dirname) {
    return mkdir(dirname, 0755);
}

int write_to_file(const char* filename, const char* data) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file\n");
        return -1;
    }

    fputs(data, fp);
    fclose(fp);

    return 0;
}