#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    //#include "info_page.html"

    void *handle_request(void *);

    int main() {
        pthread_t thread;
        int listen_fd, connect_fd;
        socklen_t client_addr_size;
        struct sockaddr_in server_addr, client_addr;
        char request[1024];

        // create a socket
        if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("socket");
            exit(-1);
        }

        // set up the server address struct
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;
        server_addr.sin_port = htons(1234);

        // bind the socket to our specified IP and port
        if (bind(listen_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
            perror("bind");
            exit(-1);
        }

        // mark the socket for listening in
        if (listen(listen_fd, 5) == -1) {
            perror("listen");
            exit(-1);
        }

        printf("Server listening on port %d\n", server_addr.sin_port);

        // loop infinitely, waiting for connections
        while (1) {
            client_addr_size = sizeof(client_addr);

            // accept a new connection
            if ((connect_fd = accept(listen_fd, (struct sockaddr *) &client_addr, &client_addr_size)) == -1) {
                perror("accept");
                exit(-1);
            }

            printf("Client connected\n");

            // create a new thread to handle the request
            if (pthread_create(&thread, NULL, handle_request, &connect_fd) != 0) {
                perror("pthread_create");
                exit(-1);
            }
        }
    }

    void *handle_request(void *ptr) {
        // get the file descriptor from the pointer we passed to pthread_create
        int connect_fd = *((int *) ptr);

        char request[1024];
        read(connect_fd, request, 1024);
        printf("%s\n", request);

        const char *response = "HTTP/1.1 200 OK\r\n"
                               "Content-Type: text/html; charset=UTF-8\r\n"
                               "\r\n"
                               "<!DOCTYPE html><html lang=\"en\"><head>"
                               "<meta charset=\"UTF-8\"><title>Info</title></head><body>"
                               "<h1>Info Page</h1>"
                               "<p>email: example@example.com</p>"
                               "<p>social security number: 1234</p>"
                               "</body></html>";
        write(connect_fd, response, strlen(response));

        // close the socket file descriptor
        close(connect_fd);
    }