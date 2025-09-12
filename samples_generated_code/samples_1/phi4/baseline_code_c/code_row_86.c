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
    KeyValuePair **pairs;
    size_t count;
} KeyValuePairs;

KeyValuePairs parse_query(const char *query) {
    KeyValuePairs kvs = {NULL, 0};
    const char *start = query;
    while (*start) {
        KeyValuePair *pair = malloc(sizeof(KeyValuePair));
        pair->key = strdup(strsep(&start, "="));
        pair->value = strdup(start);
        start = strchr(start, '&');
        if (start) start++;
        
        kvs.count++;
        kvs.pairs = realloc(kvs.pairs, sizeof(KeyValuePair*) * kvs.count);
        kvs.pairs[kvs.count - 1] = pair;
    }
    return kvs;
}

void free_key_value_pairs(KeyValuePairs kvs) {
    for (size_t i = 0; i < kvs.count; ++i) {
        free(kvs.pairs[i]->key);
        free(kvs.pairs[i]->value);
        free(kvs.pairs[i]);
    }
    free(kvs.pairs);
}

const char* get_value_from_pairs(KeyValuePairs kvs, const char *key) {
    for (size_t i = 0; i < kvs.count; ++i) {
        if (strcmp(kvs.pairs[i]->key, key) == 0) {
            return kvs.pairs[i]->value;
        }
    }
    return NULL;
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
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            continue;
        }
        
        char buffer[1024] = {0};
        read(new_socket, buffer, 1023);

        KeyValuePairs kvs = parse_query(buffer);
        const char *payload = get_value_from_pairs(kvs, "payload");

        if (!payload) {
            const char *response = "Error: Missing 'payload' parameter.";
            send(new_socket, response, strlen(response), 0);
        } else {
            // Simple YAML parsing for demonstration
            if (strstr(payload, "type: Create") != NULL) {
                const char *response = "Error: Type 'Create' is not allowed.";
                send(new_socket, response, strlen(response), 0);
            } else {
                const char *response = "Payload received successfully.";
                send(new_socket, response, strlen(response), 0);
            }
        }

        free_key_value_pairs(kvs);
        close(new_socket);
    }

    return 0;
}