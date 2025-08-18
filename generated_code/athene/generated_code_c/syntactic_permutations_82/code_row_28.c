#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    size_t count;
    KeyValuePair **pairs;
} Dictionary;

Dictionary *create_dictionary() {
    Dictionary *dict = malloc(sizeof(Dictionary));
    dict->count = 0;
    dict->pairs = NULL;
    return dict;
}

void add_to_dict(Dictionary *dict, const char *key, const char *value) {
    KeyValuePair *pair = malloc(sizeof(KeyValuePair));
    pair->key = strdup(key);
    pair->value = strdup(value);

    dict->count++;
    dict->pairs = realloc(dict->pairs, dict->count * sizeof<KeyValuePair *));
    dict->pairs[dict->count - 1] = pair;
}

char *get_from_dict(Dictionary *dict, const char *key) {
    for (size_t i = 0; i < dict->count; i++) {
        if (strcmp(dict->pairs[i]->key, key) == 0) {
            return dict->pairs[i]->value;
        }
    }
    return NULL;
}

void free_dictionary(Dictionary *dict) {
    for (size_t i = 0; i < dict->count; i++) {
        free(dict->pairs[i]->key);
        free(dict->pairs[i]->value);
        free(dict->pairs[i]);
    }
    free(dict->pairs);
    free(dict);
}

void parse_payload(Dictionary *dict, const char *payload) {
    char *dup = strdup(payload);
    char *saveptr;
    char *pair;

    for (pair = strtok_r(dup, "&", &saveptr); pair; pair = strtok_r(NULL, "&", &saveptr)) {
        char *key, *value;
        key = strtok(pair, "=");
        value = strtok(NULL, "=");
        if (key && value) {
            add_to_dict(dict, key, value);
        }
    }

    free(dup);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *response_404 = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain; charset=UTF-8\r\nContent-Length: 9\r\nConnection: close\r\n\r\nNot Found";
    const char *response_start = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: ";
    const char *response_end = "\r\nConnection: close\r\n\r\n";

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
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

    while(1) {
        printf("Listening on port %d\n", PORT);
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }
        int valread = read(new_socket, buffer, BUFFER_SIZE);
        char *method = strtok(buffer, " ");
        char *path = strtok(NULL, " ");
        char *version = strtok(NULL, "\r\n");

        if (strcmp(method, "GET") == 0 && strcmp(path, "/api") == 0) {
            char *query_start = strchr(path + strlen("/api"), '?');
            if (query_start != NULL) {
                query_start++;
                Dictionary *dict = create_dictionary();
                parse_payload(dict, query_start);
                const char *name = get_from_dict(dict, "payload");
                int name_len = name ? strlen(name) : 0;
                char content_length[12];
                snprintf(content_length, sizeof(content_length), "%d", name_len + 4); // for {"name":"..."}
                char response[BUFFER_SIZE];
                sprintf(response, "%s%s%s{\"name\":\"%s\"}", response_start, content_length, response_end, name ? name : "");
                send(new_socket, response, strlen(response), 0);
                free_dictionary(dict);
            } else {
                send(new_socket, response_404, strlen(response_404), 0);
            }
        } else {
            send(new_socket, response_404, strlen(response_404), 0);
        }

        close(new_socket);
    }

    return 0;
}