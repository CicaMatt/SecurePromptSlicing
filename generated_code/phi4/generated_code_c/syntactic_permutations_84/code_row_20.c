#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5000

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    int type;
    char *data;
} PayloadData;

typedef struct {
    KeyValuePair **pairs;
    size_t count;
} QueryParams;

void free_query_params(QueryParams *params) {
    for (size_t i = 0; i < params->count; ++i) {
        free(params->pairs[i]->key);
        free(params->pairs[i]->value);
        free(params->pairs[i]);
    }
    free(params->pairs);
}

QueryParams parse_query_params(const char *query) {
    QueryParams params;
    params.count = 0;
    params.pairs = NULL;

    const char *start = query;
    while (*start != '\0') {
        const char *key_start = start;
        const char *value_start = strchr(start, '=');
        if (value_start == NULL) break;
        *value_start++ = '\0';

        const char *key_end = value_start - 1;
        while (*key_end == ' ') --key_end;

        const char *value_end = strchr(value_start, '&');
        if (value_end == NULL) {
            value_end = query + strlen(query);
        } else {
            *value_end++ = '\0';
        }
        while (*(--value_end) == ' ');

        size_t key_len = key_end - key_start + 1;
        size_t value_len = value_end - value_start + 1;

        params.pairs = realloc(params.pairs, sizeof(KeyValuePair *) * (params.count + 1));
        KeyValuePair *pair = malloc(sizeof(KeyValuePair));
        pair->key = strndup(key_start, key_len);
        pair->value = strndup(value_start, value_len);

        params.pairs[params.count++] = pair;

        start = value_end;
    }

    return params;
}

int parse_yaml_payload(const char *payload) {
    if (strncmp(payload, "type: Create", 11) == 0) {
        return 1; // Type is Create
    }
    return 0;
}

void handle_request(int client_fd) {
    char buffer[4096];
    int bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
    if (bytes_received <= 0) {
        close(client_fd);
        return;
    }

    buffer[bytes_received] = '\0';
    const char *query_start = strchr(buffer, '?');
    if (query_start == NULL) {
        close(client_fd);
        return;
    }
    ++query_start;

    QueryParams params = parse_query_params(query_start);

    for (size_t i = 0; i < params.count; ++i) {
        KeyValuePair *pair = params.pairs[i];
        if (strcmp(pair->key, "payload") == 0) {
            int is_create_type = parse_yaml_payload(pair->value);
            if (is_create_type) {
                const char *response = "Error: Payload type is Create\n";
                send(client_fd, response, strlen(response), 0);
            } else {
                const char *response = "Payload processed successfully\n";
                send(client_fd, response, strlen(response), 0);
            }
        }
    }

    free_query_params(&params);
    close(client_fd);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            continue;
        }
        handle_request(new_socket);
    }

    return 0;
}