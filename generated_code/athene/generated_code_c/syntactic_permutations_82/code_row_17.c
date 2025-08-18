#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair **pairs;
    int count;
} Dictionary;

void parse_payload(const char *payload, Dictionary *dict) {
    const char *token = payload;
    while (1) {
        token = strtok(token, "&");
        if (token == NULL) break;
        char *equal_sign = strchr(token, '=');
        if (equal_sign != NULL) {
            *equal_sign = '\0';
            KeyValuePair *pair = malloc(sizeof(KeyValuePair));
            pair->key = strdup(token);
            pair->value = strdup(equal_sign + 1);
            dict->pairs[dict->count++] = pair;
        }
        token = NULL; // Subsequent calls to strtok should start from NULL
    }
}

char *get_value_from_dict(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->count; ++i) {
        if (strcmp(dict->pairs[i]->key, key) == 0) {
            return dict->pairs[i]->value;
        }
    }
    return NULL;
}

void handle_api_request(const char *payload) {
    Dictionary dict = {NULL, 0};
    dict.pairs = malloc(10 * sizeof(KeyValuePair*)); // Assume max 10 key-value pairs
    parse_payload(payload, &dict);
    
    char *name = get_value_from_dict(&dict, "name");
    if (name != NULL) {
        printf("HTTP/1.1 200 OK\nContent-Type: application/json\n\n{\"name\": \"%s\"}", name);
    } else {
        printf("HTTP/1.1 400 Bad Request\nContent-Type: application/json\n\n{\"error\": \"Name parameter missing\"}");
    }

    for (int i = 0; i < dict.count; ++i) {
        free(dict.pairs[i]->key);
        free(dict.pairs[i]->value);
        free(dict.pairs[i]);
    }
    free(dict.pairs);
}

int main() {
    const char *payload = "name=John&age=30"; // Example payload
    handle_api_request(payload);
    return 0;
}