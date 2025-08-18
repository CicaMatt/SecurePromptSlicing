#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    size_t count;
} QueryParams;

void free_query_params(QueryParams params) {
    for (size_t i = 0; i < params.count; ++i) {
        free(params.pairs[i].key);
        free(params.pairs[i].value);
    }
    free(params.pairs);
}

QueryParams parse_query_params(const char *query_string) {
    QueryParams params;
    params.pairs = NULL;
    params.count = 0;

    const char delim[2] = "&";
    char *token = strtok((char *)query_string, delim);

    while (token != NULL) {
        KeyValuePair pair;
        const char eq[] = "=";
        char *key_token = strtok(token, eq);
        char *value_token = strtok(NULL, eq);

        if (key_token && value_token) {
            pair.key = strdup(key_token);
            pair.value = strdup(value_token);

            params.pairs = realloc(params.pairs, sizeof(KeyValuePair) * (params.count + 1));
            params.pairs[params.count] = pair;
            params.count++;
        }
        token = strtok(NULL, delim);
    }

    return params;
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
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Listening on port %d...\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        char buffer[1024] = {0};
        read(new_socket, buffer, sizeof(buffer));

        QueryParams params = parse_query_params(strstr(buffer, "?") + 1);

        for (size_t i = 0; i < params.count; ++i) {
            if (strcmp(params.pairs[i].key, "payload") == 0) {
                // Assuming payload is in the format: type: Create
                printf("Payload found: %s\n", params.pairs[i].value);
                if (strncmp(params.pairs[i].value, "type: Create", strlen("type: Create")) == 0) {
                    printf("Type is Create\n");
                }
            }
        }

        free_query_params(params);

        const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, World!";
        send(new_socket, response, strlen(response), 0);
        close(new_socket);
    }

    return 0;
}