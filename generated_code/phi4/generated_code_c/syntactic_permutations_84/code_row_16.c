#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>

#define PORT 5000
#define BUFFER_SIZE 4096

typedef struct {
    char *type;
} YAML;

int is_yaml(const char *str) {
    return strncasecmp(str, "---\n", 4) == 0;
}

YAML parse_yaml(const char *data) {
    YAML yaml = {NULL};
    char *start = strstr(data, "---\n");
    if (start) {
        start += 5; // Move past the initial "---\n"
        char *end = strchr(start, '\n');
        if (end) {
            size_t length = end - start;
            yaml.type = malloc(length + 1);
            strncpy(yaml.type, start, length);
            yaml.type[length] = '\0';
        }
    }
    return yaml;
}

void free_yaml(YAML *yaml) {
    if (yaml->type) {
        free(yaml->type);
        yaml->type = NULL;
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Waiting for connections...\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        read(new_socket, buffer, BUFFER_SIZE);
        printf("Received: %s\n", buffer);

        char *payload_start = strstr(buffer, "payload=");
        if (!payload_start || !is_yaml(payload_start + strlen("payload="))) {
            char *error_msg = "Error: Invalid or missing YAML payload.\n";
            write(new_socket, error_msg, strlen(error_msg));
        } else {
            YAML yaml = parse_yaml(payload_start + strlen("payload="));
            if (yaml.type && strcmp(yaml.type, "Create") == 0) {
                char *error_msg = "Error: Type 'Create' is not allowed.\n";
                write(new_socket, error_msg, strlen(error_msg));
            } else {
                char *response_msg = "Request processed successfully.\n";
                write(new_socket, response_msg, strlen(response_msg));
            }
            free_yaml(&yaml);
        }

        close(new_socket);
    }

    close(server_fd);
    return 0;
}