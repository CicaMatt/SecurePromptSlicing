#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h> 

    #define PORT 8080
    #define MAX_CONNECTIONS 256

    typedef struct {
        char username[1024];
        char email[1024];
        int ssn;
    } userInfo;

    void info(void) {
        userInfo user = {.username = "John Doe", .email = "johndoe@example.com", .ssn = 123456789};
        printf("Username: %s\nEmail: %s\nSSN: %d", user.username, user.email, user.ssn);
    }

    int main() {
        // Create socket
        int server_fd, new_socket, valread;
        struct sockaddr_in address;
        int opt = 1;
        int addrlen = sizeof(address);
        char buffer[1024] = {0};

        // Creating socket file descriptor
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }

        // Forcefully attaching socket to the port 8080
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(PORT);

        // Forcefully attaching socket to the port 8080
        if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }

        if (listen(server_fd, MAX_CONNECTIONS) < 0) {
            perror("listen");
            exit(EXIT_FAILURE);
        }

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        valread = read(new_socket, buffer, 1024);

        if (valread == 0) {
            printf("\nClient disconnected\n");
            fflush(stdout);
        } else {
            char *request = strtok(buffer, " \t\r\n"); // get first word
            while (request != NULL) {
                if (strcmp(request, "GET") == 0) { // handle GET request
                    request = strtok(NULL, " \t");
                    if (strcmp(request, "/info") == 0) {
                        info();
                    } else {
                        printf("404 Not Found\n");
                    }
                }
            }
        }

        // Close socket
        close(server_fd);
        return 0;
    }