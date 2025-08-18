#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

// Function to check if a string is YAML
int is_yaml(const char *data, size_t len) {
    for (size_t i = 0; i < len - 3; ++i) {
        if (data[i] == '-' && data[i + 1] == ' ' &&
            isalnum(data[i + 2]) && data[i + 3] == ':') {
            return 1;
        }
    }
    return 0;
}

// Function to check if the YAML payload type is "Create"
int yaml_type_is_create(const char *data, size_t len) {
    const char *create_str = ":type: Create";
    size_t create_len = strlen(create_str);

    for (size_t i = 0; i < len - create_len; ++i) {
        if (!strncmp(data + i, create_str, create_len)) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 5000
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(5000);

    // Binding the socket to the port 5000
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listening for connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    printf("Listening on port 5000...\n");

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                                 (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        char buffer[BUFFER_SIZE] = {0};
        int bytes_read = read(new_socket, buffer, BUFFER_SIZE - 1);

        if (bytes_read <= 0) {
            printf("Connection closed or error occurred\n");
            close(new_socket);
            continue;
        }

        printf("Request received:\n%s\n", buffer);

        // Check for YAML payload
        if (!is_yaml(buffer, bytes_read)) {
            const char *error_message = "Invalid request: Not a valid YAML format.";
            send(new_socket, error_message, strlen(error_message), 0);
            close(new_socket);
            continue;
        }

        // Check if the payload type is Create
        if (yaml_type_is_create(buffer, bytes_read)) {
            const char *error_message = "Invalid request: Payload type 'Create' not allowed.";
            send(new_socket, error_message, strlen(error_message), 0);
            close(new_socket);
            continue;
        }

        // Respond with success message
        const char *success_message = "Request processed successfully.\n";
        send(new_socket, success_message, strlen(success_message), 0);

        printf("Processed request successfully\n");
        close(new_socket);
    }

    return 0;
}