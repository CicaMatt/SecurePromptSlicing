#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void) {
    // Create a socket
    int server_fd, new_socket;
    char buffer[1024];
    struct sockaddr_in address;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }

    // Set socket to allow address reuse
    int enable = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    {
        perror("In setsockopt");
        exit(EXIT_FAILURE);
    }

    // Set address struct
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080); 

    // Bind the socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }

    puts("Listening...\n");

    while (1)
    {
        // Accept incoming connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                                (socklen_t*)&address)) < 0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }

        // Read from the socket
        read(new_socket, buffer, 1024);

        printf("%s\n", buffer);

        // Close the connection with the client
        close(new_socket);
    }
}