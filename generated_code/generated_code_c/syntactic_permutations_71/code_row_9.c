#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 64

int main(void) {
    int socket_fd, port = 5001;
    struct sockaddr_in server, client;
    char buffer[BUFFER_SIZE];

    // Create a new TCP socket.
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(-1);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if (bind(socket_fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("binding failed");
        exit(-1);
    }

    listen(socket_fd, 3);

    printf("Server is up and running on port %d\n", port);

    for (;;) {
        socklen_t client_size = sizeof(client);
        int new_socket;

        if ((new_socket = accept(socket_fd, (struct sockaddr *)&client, &client_size)) < 0) {
            perror("accepting connection failed");
            exit(-1);
        }

        printf("New client connected\n");

        recv(new_socket, buffer, BUFFER_SIZE, 0);
        printf("%s\n", buffer);

        send(new_socket, "Hello from server\n", 64, 0);
        close(new_socket);
    }

    return 0;
}