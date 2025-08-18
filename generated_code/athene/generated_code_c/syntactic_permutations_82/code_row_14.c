#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    int count;
    KeyValuePair **pairs;
} Dictionary;

Dictionary *create_dictionary() {
    Dictionary *dict = malloc(sizeof(Dictionary));
    dict->count = 0;
    dict->pairs = NULL;
    return dict;
}

void add_to_dictionary(Dictionary *dict, const char *key, const char *value) {
    dict->pairs = realloc(dict->pairs, (dict->count + 1) * sizeof(KeyValuePair*));
    KeyValuePair *pair = malloc(sizeof(KeyValuePair));
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
    const char *token;
    token = strtok((char *)payload, "&");
    while (token != NULL) {
        const char *equals = strchr(token, '=');
        if (equals) {
            int key_len = equals - token;
            char key[key_len + 1];
            strncpy(key, token, key_len);
            key[key_len] = '\0';
            add_to_dictionary(dict, key, equals + 1);
        }
        token = strtok(NULL, "&");
    }

    char *name = get_from_dictionary(dict, "name");
    free_dictionary(dict);
    return name;
}

void handle_api_request(const char *url) {
    const char *payload_start = strstr(url, "?") + 1;
    if (payload_start[0] == '\0') payload_start = "";
    char *name = parse_payload(payload_start);
    printf("HTTP/1.1 200 OK\nContent-Type: application/json\n\n{\"name\": \"%s\"}", name ? name : "");
    free(name);
}

int main() {
    const char *url = "/api?payload=name=John&age=30";
    handle_api_request(url);
    return 0;
}