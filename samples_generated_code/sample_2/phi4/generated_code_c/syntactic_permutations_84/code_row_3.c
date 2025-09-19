#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <yaml.h>

#define PORT 5000

void handle_request(int client_socket) {
    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, sizeof(buffer));
    
    if (valread > 0) {
        char *payload_start = strstr(buffer, "payload=");
        if (payload_start) {
            payload_start += strlen("payload=");

            yaml_parser_t parser;
            yaml_event_t event;

            FILE *fp = fmemopen(payload_start, strlen(payload_start), "r");
            if (!fp) {
                write(client_socket, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\n\r\n", 50);
                close(client_socket);
                return;
            }

            yaml_parser_initialize(&parser);
            yaml_parser_set_input_file(&parser, fp);

            if (yaml_parser_parse(&parser, &event) && event.type == YAML_STREAM_START_EVENT) {
                do {
                    if (event.type == YAML_DOCUMENT_START_EVENT) {
                        if (yaml_parser_parse(&parser, &event)) {
                            if (event.type == YAML_SCALAR_EVENT) {
                                if (strcmp(event.data.scalar.value, "Create") == 0) {
                                    write(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 22\r\n\r\nError: Invalid operation", 59);
                                    break;
                                }
                            }
                        }
                    }
                } while (yaml_parser_parse(&parser, &event));
            }

            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            fclose(fp);

            write(client_socket, "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n", 35);
        } else {
            write(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n", 38);
        }
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
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

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        handle_request(new_socket);
    }

    return 0;
}