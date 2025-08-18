#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define PORT 5000

typedef struct {
    char* key;
    char* value;
} Header;

void free_headers(Header* headers, int count) {
    for (int i = 0; i < count; ++i) {
        free(headers[i].key);
        free(headers[i].value);
    }
    free(headers);
}

char* get_header_value(Header* headers, int header_count, const char* key) {
    for (int i = 0; i < header_count; ++i) {
        if (strcmp(headers[i].key, key) == 0) {
            return headers[i].value;
        }
    }
    return NULL;
}

char** split_string(const char* str, const char delimiter, int* count) {
    char* str_copy = strdup(str);
    char* token = strtok(str_copy, &delimiter);
    int size = 10;
    *count = 0;

    char** result = malloc(size * sizeof(char*));
    while (token != NULL) {
        if (*count >= size) {
            size *= 2;
            result = realloc(result, size * sizeof(char*));
        }
        result[(*count)++] = strdup(token);
        token = strtok(NULL, &delimiter);
    }

    free(str_copy);
    return result;
}

int is_yaml_create(const char* yaml_content) {
    const char* type_key = "type: Create\n";
    size_t len = strlen(type_key);

    if (strncmp(yaml_content, type_key, len) == 0) {
        return 1;
    }
    return 0;
}

void handle_request(Header* headers, int header_count) {
    char* payload_value = get_header_value(headers, header_count, "payload");

    if (payload_value == NULL) {
        printf("HTTP/1.1 400 Bad Request\nContent-Type: text/plain\n\nError: Missing 'payload' parameter.\n");
        return;
    }

    int yaml_length;
    char** lines = split_string(payload_value, '\n', &yaml_length);
    char* yaml_content = malloc(strlen(lines[0]) + 1);

    strcpy(yaml_content, lines[0]);

    for (int i = 1; i < yaml_length; ++i) {
        strcat(yaml_content, "\n");
        strcat(yaml_content, lines[i]);
    }

    if (is_yaml_create(yaml_content)) {
        printf("HTTP/1.1 400 Bad Request\nContent-Type: text/plain\n\nError: 'type' cannot be 'Create'.\n");
    } else {
        printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\nPayload processed successfully.\n");
    }

    free(yaml_content);
    for (int i = 0; i < yaml_length; ++i) {
        free(lines[i]);
    }
    free(lines);
}

void start_server(int port) {
    // Simulated server loop
    while (1) {
        // Simulating a request with headers and payload
        Header headers[] = {
            {"payload", "type: Create\nname: Example\n"},
            {NULL, NULL}
        };

        int header_count = 0;
        for (Header* h = headers; h->key != NULL; ++h) {
            ++header_count;
        }

        handle_request(headers, header_count);
    }
}

int main() {
    start_server(PORT);
    return 0;
}