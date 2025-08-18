#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5000

void handle_request(int client_fd) {
    char buffer[4096];
    int bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);

    if (bytes_received <= 0) return;

    buffer[bytes_received] = '\0';

    // Simple parsing to check for "payload" parameter
    if (strstr(buffer, "payload=")) {
        char *payload_start = strstr(buffer, "payload=") + strlen("payload=");
        char payload_str[strlen(payload_start)];
        strcpy(payload_str, payload_start);

        yaml_parser_t parser;
        FILE *fp = fmemopen((void *)payload_str, strlen(payload_str), "r");
        if (!fp) {
            close(client_fd);
            return;
        }

        yaml_parser_initialize(&parser);
        yaml_parser_set_input_file(&parser, fp);

        yaml_event_t event;
        while (yaml_parser_parse(&parser, &event)) {
            if (event.type == YAML_MAPPING_START_EVENT) {
                char key[256];
                char value[256];

                while (1) {
                    yaml_parser_parse(&parser, &event);
                    if (event.type == YAML_KEY_EVENT) {
                        strncpy(key, event.data.scalar.value, sizeof(key));
                    }
                    else if (event.type == YAML_VALUE_EVENT) {
                        strncpy(value, event.data.scalar.value, sizeof(value));

                        if (strcmp(key, "type") == 0 && strcmp(value, "Create") == 0) {
                            const char *error_msg = "Error: Create type not allowed.\n";
                            send(client_fd, error_msg, strlen(error_msg), 0);
                            break;
                        }
                    }

                    if (event.type == YAML_MAPPING_END_EVENT || event.type == YAML_SEQUENCE_END_EVENT)
                        break;
                }
            }
        }

        yaml_parser_delete(&parser);
        fclose(fp);

        close(client_fd);
    } else {
        const char *response = "No payload found.\n";
        send(client_fd, response, strlen(response), 0);
    }

    close(client_fd);
}

int main() {
    int server_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
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

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        int client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }
        handle_request(client_fd);
    }

    close(server_fd);
    return 0;
}