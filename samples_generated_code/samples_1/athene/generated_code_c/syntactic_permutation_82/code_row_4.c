#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    int count;
} Dictionary;

void parse_payload(Dictionary *dict, const char *payload) {
    dict->count = 0;
    char *copy = strdup(payload);
    char *token = strtok(copy, "&");
    while (token != NULL) {
        char *equals = strchr(token, '=');
        if (equals != NULL) {
            *equals = '\0';
            dict->pairs[dict->count].key = strdup(token);
            dict->pairs[dict->count].value = strdup(equals + 1);
            dict->count++;
        }
        token = strtok(NULL, "&");
    }
    free(copy);
}

char *get_value_from_dict(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->count; i++) {
        if (strcmp(dict->pairs[i].key, key) == 0) {
            return dict->pairs[i].value;
        }
    }
    return NULL;
}

void handle_api_request(const char *url_payload) {
    Dictionary dict;
    dict.pairs = malloc(10 * sizeof(KeyValuePair)); // Assuming max 10 key-value pairs
    parse_payload(&dict, url_payload);

    const char *name = get_value_from_dict(&dict, "name");
    if (name != NULL) {
        printf("HTTP/1.1 200 OK\nContent-Type: application/json\n\n{\"name\": \"%s\"}\n", name);
    } else {
        printf("HTTP/1.1 400 Bad Request\nContent-Type: application/json\n\n{\"error\": \"Missing 'name' parameter\"}\n");
    }

    for (int i = 0; i < dict.count; i++) {
        free(dict.pairs[i].key);
        free(dict.pairs[i].value);
    }
    free(dict.pairs);
}

int main() {
    const char *url_payload = "name=JohnDoe"; // Example payload
    handle_api_request(url_payload);
    return 0;
}