#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 4096

typedef struct {
    char *key;
    char *value;
} KeyValue;

KeyValue *parse_query_string(const char *query, int *count) {
    const char *token = query;
    int n = 0;
    while (*token) {
        if (*token == '&') {
            n++;
        }
        token++;
    }
    n++;

    KeyValue *kv = malloc(n * sizeof(KeyValue));
    *count = n;

    token = query;
    for (int i = 0; i < n; i++) {
        kv[i].key = NULL;
        kv[i].value = NULL;
        char *equals = strchr(token, '=');
        if (equals) {
            kv[i].key = strndup(token, equals - token);
            kv[i].value = strdup(equals + 1);
            token = strchr(kv[i].value, '&');
            if (token) {
                *token = '\0';
                token++;
            }
        }
    }

    return kv;
}

char *get_name_from_query(KeyValue *kv, int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(kv[i].key, "payload") == 0) {
            char *payload = kv[i].value;
            KeyValue payload_kv[1];
            const char *name_token = strstr(payload, "name=");
            if (name_token) {
                name_token += 5; // Skip "name="
                char *end_name = strchr(name_token, '&');
                int len = end_name ? end_name - name_token : strlen(name_token);
                return strndup(name_token, len);
            }
        }
    }
    return NULL;
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE);

    if (strstr(buffer, "GET /api?") != NULL) {
        const char *query_start = strstr(buffer, "?") + 1;
        const char *http_start = strstr(query_start, " HTTP");
        int query_length = http_start - query_start;

        char query[query_length + 1];
        strncpy(query, query_start, query_length);
        query[query_length] = '\0';

        int kv_count;
        KeyValue *kv = parse_query_string(query, &kv_count);

        char *name = get_name_from_query(kv, kv_count);
        if (name) {
            char response[] = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"name\":\"%s\"}";
            int len = snprintf(NULL, 0, response, name);
            char *final_response = malloc(len + 1);
            sprintf(final_response, response, name);
            write(client_socket, final_response, strlen(final_response));
            free(final_response);
        } else {
            const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"error\":\"Name not found\"}";
            write(client_socket, response, strlen(response));
        }

        for (int i = 0; i < kv_count; i++) {
            free(kv[i].key);
            free(kv[i].value);
        }
        free(kv);
        free(name);
    } else {
        const char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot Found";
        write(client_socket, response, strlen(response));
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

    if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0) {
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
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }
        handle_request(new_socket);
        close(new_socket);
    }

    return 0;
}