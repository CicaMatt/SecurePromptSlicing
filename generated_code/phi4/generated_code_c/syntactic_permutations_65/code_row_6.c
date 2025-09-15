#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        error("socket failed");
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        error("setsockopt");
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Binding the socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        error("bind failed");
    }

    // Listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        error("listen");
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            error("accept");
        }

        char buffer[BUFFER_SIZE] = {0};
        long valread = read(new_socket, buffer, BUFFER_SIZE);
        
        // Assuming the first message contains the filename
        char filename[256];
        sscanf(buffer, "filename: %s", filename);

        char filepath[512];
        snprintf(filepath, sizeof(filepath), "./uploads/%s.pdf", filename);

        FILE *file = fopen(filepath, "wb");
        if (!file) {
            error("fopen");
        }

        while ((valread = read(new_socket, buffer, BUFFER_SIZE)) > 0) {
            fwrite(buffer, 1, valread, file);
        }
        
        fclose(file);
        printf("File %s uploaded successfully\n", filename);

        char *message = "File received";
        send(new_socket, message, strlen(message), 0);
        close(new_socket);
    }

    return 0;
}
