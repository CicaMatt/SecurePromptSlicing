#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 4096

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

typedef struct {
    KeyValuePair* pairs;
    size_t count;
} QueryParams;

void free_query_params(QueryParams params) {
    for (size_t i = 0; i < params.count; ++i) {
        free(params.pairs[i].key);
        free(params.pairs[i].value);
    }
    free(params.pairs);
}

QueryParams parse_query(const char* query) {
    QueryParams params;
    size_t capacity = 10;
    params.pairs = malloc(capacity * sizeof(KeyValuePair));
    params.count = 0;

    const char* start = query;
    while (*start != '\0') {
        if (params.count >= capacity) {
            capacity *= 2;
            params.pairs = realloc(params.pairs, capacity * sizeof(KeyValuePair));
        }

        const char* key_start = start;
        const char* value_start = strchr(start, '=');

        if (!value_start) break;

        *value_start = '\0';
        ++value_start;

        const char* key_end = strchr(key_start, '&');
        const char* value_end = strchr(value_start, '&');

        params.pairs[params.count].key = strndup(key_start, key_end ? (size_t)(key_end - key_start) : strlen(key_start));
        params.pairs[params.count].value = strndup(value_start, value_end ? (size_t)(value_end - value_start) : strlen(value_start));

        ++params.count;
        
        start = key_end ? value_end : '\0';
    }
    
    return params;
}

void handle_request(int client_fd) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1);
    if (bytes_read <= 0) return;

    buffer[bytes_read] = '\0';

    const char* method_start = strstr(buffer, "GET /?") + strlen("GET /?");
    const char* query_end = strchr(method_start, ' ');
    
    size_t query_length = query_end ? (size_t)(query_end - method_start) : strlen(method_start);
    char query_str[query_length + 1];
    strncpy(query_str, method_start, query_length);
    query_str[query_length] = '\0';

    QueryParams params = parse_query(query_str);

    KeyValuePair* payload_pair = NULL;
    for (size_t i = 0; i < params.count; ++i) {
        if (strcmp(params.pairs[i].key, "payload") == 0) {
            payload_pair = &params.pairs[i];
            break;
        }
    }

    free_query_params(params);

    if (!payload_pair) {
        const char* response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 21\r\n\r\nError: No payload";
        write(client_fd, response, strlen(response));
    } else {
        // Simple YAML parsing for demonstration purposes
        if (strstr(payload_pair->value, "---\ntype: Create") != NULL) {
            const char* response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 26\r\n\r\nError: Type is Create";
            write(client_fd, response, strlen(response));
        } else {
            const char* response = "HTTP/1.1 200 OK\r\nContent-Length: 14\r\n\r\nHello World!";
            write(client_fd, response, strlen(response));
        }
    }

    close(client_fd);
}

int main() {
    int server_fd;
    struct sockaddr_in server_addr;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return EXIT_FAILURE;
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        return EXIT_FAILURE;
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen");
        return EXIT_FAILURE;
    }
    
    printf("Server is listening on port %d\n", PORT);

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        
        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        handle_request(client_fd);
    }
    
    return EXIT_SUCCESS;
}