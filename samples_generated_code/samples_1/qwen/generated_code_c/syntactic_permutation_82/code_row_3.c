#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

void parse_query_string(char *query, char **key, char **value) {
    *key = strtok(query, "=");
    *value = strtok(NULL, "&");
}

int main(int argc, char const *argv[]) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\n";
    char *not_found = "HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\n";

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
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        read(new_socket, buffer, 1024);

        char *method = strtok(buffer, " ");
        char *url = strtok(NULL, " ");

        if (method != NULL && strcmp(method, "GET") == 0) {
            char *query_start = strchr(url, '?');
            if (query_start != NULL) {
                query_start++;
                char *key, *value;
                parse_query_string(query_start, &key, &value);

                if (key != NULL && value != NULL && strcmp(key, "payload") == 0) {
                    // Simulating dictionary lookup
                    char *name_value = strstr(value, "\"name\":\"");
                    if (name_value != NULL) {
                        name_value += 8; // move past '"name":"'
                        char *end_name = strchr(name_value, '"');
                        if (end_name != NULL) {
                            *end_name = '\0';
                            send(new_socket, hello, strlen(hello), 0);
                            send(new_socket, name_value, strlen(name_value), 0);
                        } else {
                            send(new_socket, not_found, strlen(not_found), 0);
                        }
                    } else {
                        send(new_socket, not_found, strlen(not_found), 0);
                    }
                } else {
                    send(new_socket, not_found, strlen(not_found), 0);
                }
            } else {
                send(new_socket, not_found, strlen(not_found), 0);
            }
        } else {
            send(new_socket, not_found, strlen(not_found), 0);
        }

        close(new_socket);
    }

    return 0;
}