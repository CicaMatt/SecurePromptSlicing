#include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <netdb.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <sys/wait.h>
    #include <arpa/inet.h>

    #define PORT "5000"
    #define BACKLOG 10
    #define MAXDATASIZE 256

    typedef struct {
        char *name;
        char *value;
    } Parameter;

    typedef enum {
        Create,
        Read,
        Update,
        Delete
    } ParameterType;

    int main(int argc, char const *argv[]) {
        struct addrinfo hints, *res;
        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;

        struct sockaddr_storage client_address;
        char *ipstr, *portstr;
        int status, new_fd;
        socklen_t addr_size;

        if ((status = getaddrinfo(NULL, PORT, &hints, &res)) != 0) {
            fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
            exit(EXIT_FAILURE);
        }

        int listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (listenfd == -1) {
            fprintf(stderr, "socket error: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        int yes = 1;
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        if (bind(listenfd, res->ai_addr, res->ai_addrlen) == -1) {
            fprintf(stderr, "bind error: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        freeaddrinfo(res);

        if (listen(listenfd, BACKLOG) == -1) {
            fprintf(stderr, "listen error: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        char buffer[MAXDATASIZE];
        int nbytes;
        Parameter parameter;
        while (1) {
            if ((new_fd = accept(listenfd, (struct sockaddr *) &client_address, &addr_size)) == -1) {
                fprintf(stderr, "accept error: %s\n", strerror(errno));
                continue;
            }

            if ((nbytes = recv(new_fd, buffer, MAXDATASIZE, 0)) <= 0) {
                if (nbytes == 0) {
                    printf("Connection closed\n");
                } else {
                    fprintf(stderr, "recv error: %s\n", strerror(errno));
                }
                close(new_fd);
                continue;
            }

            if (strncmp(buffer, "payload=", 8) != 0) {
                char *message = "Error: no payload parameter";
                send(new_fd, message, strlen(message), 0);
                close(new_fd);
                continue;
            }

            buffer[nbytes] = '\0';
            parameter.name = strtok(buffer + 8, "=");
            parameter.value = strtok(NULL, "\r\n");

            ParameterType type = Read;
            if (strcmp(parameter.name, "Create") == 0) {
                type = Create;
            } else if (strcmp(parameter.name, "Update") == 0) {
                type = Update;
            }

            char *response = "Error: Invalid parameter";
            switch (type) {
                case Create:
                    response = "Create request received";
                    break;
                case Read:
                    response = "Read request received";
                    break;
                case Update:
                    response = "Update request received";
                    break;
            }
            send(new_fd, response, strlen(response), 0);
            close(new_fd);
        }

        return EXIT_SUCCESS;
    }