#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    int count;
    KeyValuePair **pairs;
} Dictionary;

void parse_payload(Dictionary *dict, const char *payload) {
    dict->count = 0;
    dict->pairs = NULL;
    char *copy = strdup(payload);
    char *token = strtok(copy, "&");
    while (token != NULL) {
        KeyValuePair *pair = malloc(sizeof(KeyValuePair));
        pair->key = strtok(token, "=");
        pair->value = strtok(NULL, "=");
        if (pair->key && pair->value) {
            dict->count++;
            dict->pairs = realloc(dict->pairs, sizeof(KeyValuePair *) * dict->count);
            dict->pairs[dict->count - 1] = pair;
        }
        token = strtok(NULL, "&");
    }
    free(copy);
}

const char *get_name_from_dict(Dictionary *dict) {
    for (int i = 0; i < dict->count; i++) {
        if (strcmp(dict->pairs[i]->key, "name") == 0) {
            return dict->pairs[i]->value;
        }
    }
    return NULL;
}

void free_dictionary(Dictionary *dict) {
    for (int i = 0; i < dict->count; i++) {
        free(dict->pairs[i]->key);
        free(dict->pairs[i]->value);
        free(dict->pairs[i]);
    }
    free(dict->pairs);
}

void handle_api_request(const char *url, const char *payload) {
    Dictionary dict;
    parse_payload(&dict, payload);
    const char *name = get_name_from_dict(&dict);
    if (name != NULL) {
        printf("HTTP/1.1 200 OK\nContent-Type: application/json\n\n{\"name\": \"%s\"}\n", name);
    } else {
        printf("HTTP/1.1 400 Bad Request\nContent-Type: application/json\n\n{\"error\": \"Missing 'name' parameter\"}\n");
    }
    free_dictionary(&dict);
}

int main() {
    const char *url = "/api";
    const char *payload = "name=John Doe"; // Example payload
    handle_api_request(url, payload);
    return 0;
}