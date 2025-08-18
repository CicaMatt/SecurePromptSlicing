#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    int count;
    KeyValuePair **pairs;
} Dictionary;

Dictionary *create_dictionary() {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    dict->count = 0;
    dict->pairs = NULL;
    return dict;
}

void add_to_dictionary(Dictionary *dict, const char *key, const char *value) {
    dict->pairs = (KeyValuePair **)realloc(dict->pairs, (dict->count + 1) * sizeof(KeyValuePair *));
    KeyValuePair *pair = (KeyValuePair *)malloc(sizeof(KeyValuePair));
    pair->key = strdup(key);
    pair->value = strdup(value);
    dict->pairs[dict->count++] = pair;
}

char *get_from_dictionary(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->count; i++) {
        if (strcmp(dict->pairs[i]->key, key) == 0) {
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
    free(dict);
}

char *parse_payload(const char *payload) {
    Dictionary *dict = create_dictionary();
    const char *start = payload;
    while (*payload != '\0') {
        if (*payload == '&') {
            *payload = '\0';
            add_to_dictionary(dict, start, strchr(start, '=') + 1);
            start = payload + 1;
        }
        payload++;
    }
    add_to_dictionary(dict, start, strchr(start, '=') + 1);

    char *name = get_from_dictionary(dict, "name");
    free_dictionary(dict);
    return name;
}

void handle_request(const char *url) {
    const char *payload_start = strstr(url, "?") + 1;
    char *name = parse_payload(payload_start);
    if (name != NULL) {
        printf("HTTP/1.1 200 OK\nContent-Type: application/json\n\n{\"name\": \"%s\"}\n", name);
        free(name);
    } else {
        printf("HTTP/1.1 400 Bad Request\nContent-Type: application/json\n\n{}\n");
    }
}

int main() {
    const char *url = "/api?payload=name=John Doe";
    handle_request(url);
    return 0;
}