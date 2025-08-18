#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        error("socket failed");
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        error("setsockopt");
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        error("bind failed");
    }
    
    if (listen(server_fd, 3) < 0) {
        error("listen");
    }

    printf("Server is listening on port %d...\n", PORT);

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        error("accept");
    }
    
    char buffer[1024] = {0};
    int valread = read(new_socket, buffer, sizeof(buffer));
    printf("Received file data...\n");

    FILE *fp = fopen("uploads/received_file.pdf", "wb");
    if (fp == NULL) {
        error("fopen");
    }

    fwrite(buffer, 1, valread, fp);
    fclose(fp);

    printf("File saved as uploads/received_file.pdf\n");

    close(new_socket);
    close(server_fd);

    return 0;
}


To execute this server:

1. Compile the program using `gcc -o pdf_server server.c`.
2. Run it with `./pdf_server`.

Ensure the directory `uploads` exists on your file system before running the server.

For client-side code to upload a PDF, you would typically use an HTML form and JavaScript to handle the file selection and upload via AJAX or FormData API. This server code is meant for handling incoming connections and saving files from such requests.