// import libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

// define constant variables
#define PORT 8080
#define BUFFER_SIZE 4096
#define MAX_FILE_NAME_LENGTH 256

// define struct for file data
typedef struct {
    char filename[MAX_FILE_NAME_LENGTH];
    int filesize;
    char filetype[32];
    unsigned char *filedata;
} FileData;

// function prototypes
void handle_request(int client_socket);
int recv_request(int client_socket, char **recv_buffer);
int send_response(int client_socket, const char *message);
int process_multipart_formdata(const char *formdata, FileData *file_data);

// main function
int main() {
    int server_socket, client_socket;
    struct sockaddr_in servaddr = {0};

    // create a socket and bind it to the port number
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // initialize server address structure
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // bind the socket to the port number
    if (bind(server_socket, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // mark the socket as passive (to listen for incoming connections)
    if (listen(server_socket, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // loop to handle incoming connections
    while (1) {
        if ((client_socket = accept(server_socket, NULL, NULL)) < 0) {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }

        // handle the request in a new thread
        pthread_t thread;
        pthread_create(&thread, NULL, (void *)handle_request, client_socket);
    }
}

// function to handle incoming requests
void *handle_request(int client_socket) {
    char *recv_buffer = malloc(BUFFER_SIZE);
    int bytes_received;

    // receive data from the client socket
    if ((bytes_received = recv_request(client_socket, &recv_buffer)) < 0) {
        perror("recv failed");
        exit(EXIT_FAILURE);
    }

    printf("Received %d bytes from client\n", bytes_received);

    // process the form data
    FileData file_data;
    int result = process_multipart_formdata(recv_buffer, &file_data);
    if (result < 0) {
        perror("process_multipart_formdata failed");
        exit(EXIT_FAILURE);
    }

    // send a response to the client
    char message[256];
    sprintf(message, "File %s of type %s received successfully!\n", file_data.filename, file_data.filetype);
    if (send_response(client_socket, message) < 0) {
        perror("send failed");
        exit(EXIT_FAILURE);
    }

    // close the client socket
    close(client_socket);
}

// function to receive data from a client socket
int recv_request(int client_socket, char **recv_buffer) {
    int total_bytes = 0;
    char *tmp_buffer;
    do {
        tmp_buffer = realloc(*recv_buffer, BUFFER_SIZE);
        if (tmp_buffer == NULL) {
            perror("realloc failed");
            return -1;
        }
        *recv_buffer = tmp_buffer;

        int bytes_received = read(client_socket, *recv_buffer + total_bytes, BUFFER_SIZE);
        if (bytes_received < 0) {
            perror("read failed");
            return -1;
        }
        total_bytes += bytes_received;
    } while (*(*recv_buffer + total_bytes - 1) != '\n');

    // null terminate the string
    *(*recv_buffer + total_bytes) = '\0';

    return total_bytes;
}

// function to send data to a client socket
int send_response(int client_socket, const char *message) {
    int total_bytes = 0;
    do {
        int bytes_sent = write(client_socket, message + total_bytes, strlen(message));
        if (bytes_sent < 0) {
            perror("write failed");
            return -1;
        }
        total_bytes += bytes_sent;
    } while (total_bytes < strlen(message));
}

// function to process multipart form data
int process_multipart_formdata(const char *formdata, FileData *file_data) {
    // extract the file name from the form data
    sscanf(formdata, "Content-Disposition: form-data; name=\"file\"; filename=\"%[^\"]", file_data->filename);

    // extract the file type and size from the form data
    char *content_type = strstr(formdata, "Content-Type: ");
    sscanf(content_type, "Content-Type: %s\r\n", file_data->filetype);

    int i;
    for (i = 0; formdata[i] != '\r'; i++);
    formdata += i + 2;

    // allocate memory for the file data
    int filesize = strlen(formdata);
    unsigned char *filedata = malloc(filesize);

    if (filedata == NULL) {
        perror("malloc failed");
        return -1;
    }

    // copy the file data into the buffer
    memcpy(filedata, formdata, filesize);

    // store the file data in the FileData struct
    file_data->filesize = filesize;
    file_data->filedata = filedata;
}