#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} kv_pair;

kv_pair* parse_query_string(const char *query) {
    kv_pair *pair = (kv_pair *)malloc(sizeof(kv_pair));
    pair->key = NULL;
    pair->value = NULL;

    const char *equal_sign = strchr(query, '=');
    if (equal_sign != NULL) {
        size_t key_len = equal_sign - query;
        pair->key = (char *)malloc(key_len + 1);
        strncpy(pair->key, query, key_len);
        pair->key[key_len] = '\0';

        const char *value_start = equal_sign + 1;
        pair->value = strdup(value_start);
    }
    return pair;
}

void handle_api_request(const char *query) {
    kv_pair *pair = parse_query_string(query);

    if (pair && strcmp(pair->key, "name") == 0) {
        printf("HTTP/1.1 200 OK\r\n");
        printf("Content-Type: application/json\r\n");
        printf("\r\n");
        printf("{\"name\": \"%s\"}", pair->value);
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Invalid request");
    }

    if (pair) {
        free(pair->key);
        free(pair->value);
        free(pair);
    }
}

int main() {
    const char *query = getenv("QUERY_STRING");

    if (strcmp(getenv("REQUEST_URI"), "/api") == 0 && query != NULL) {
        handle_api_request(query);
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Not found");
    }

    return 0;
}