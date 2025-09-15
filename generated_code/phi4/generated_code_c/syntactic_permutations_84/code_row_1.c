#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "yaml.h"

#define PORT 5000

void handle_request(int client_sock) {
    char buffer[1024] = {0};
    int valread = read(client_sock, buffer, sizeof(buffer));
    
    if (valread > 0 && strstr(buffer, "payload=")) {
        char *start = strchr(buffer, '=');
        start++;
        
        yaml_parser_t parser;
        FILE *file = fmemopen(start, strlen(start), "r");
        yaml_parser_initialize(&parser);
        yaml_parser_set_input_file(&parser, file);
        
        yaml_event_t event;
        if (!yaml_parse_stream(&parser, &event)) {
            fprintf(stderr, "Error parsing YAML\n");
            write(client_sock, "Internal Server Error", 19);
        } else {
            if (event.type == YAML_SCALAR_EVENT) {
                char *type = strdup((char *)event.data.scalar.value);
                if (strcmp(type, "Create") == 0) {
                    write(client_sock, "Error: Create type not allowed", 34);
                } else {
                    write(client_sock, "Request processed successfully", 31);
                }
                free(type);
            }
        }

        yaml_event_delete(&event);
        yaml_parser_delete(&parser);
        fclose(file);
    } else {
        write(client_sock, "Error: Missing payload parameter", 33);
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

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
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            continue;
        }
        
        handle_request(new_socket);

        close(new_socket);
    }

    return 0;
}
