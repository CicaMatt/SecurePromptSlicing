#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair **pairs;
    int count;
} Dictionary;

void add_to_dictionary(Dictionary *dict, const char *key, const char *value) {
    dict->pairs = realloc(dict->pairs, (dict->count + 1) * sizeof(KeyValuePair *));
    dict->pairs[dict->count] = malloc(sizeof(KeyValuePair));
    dict->pairs[dict->count]->key = strdup(key);
    dict->pairs[dict->count]->value = strdup(value);
    dict->count++;
}

char* get_from_dictionary(Dictionary *dict, const char *key) {
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
}

Dictionary* parse_payload(const char *payload) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    dict->pairs = NULL;
    dict->count = 0;

    const char *token = strtok((char *)payload, "&");
    while (token != NULL) {
        char *key = strndup(token, strcspn(token, "="));
        token += strlen(key) + 1;
        char *value = strdup(token);
        add_to_dictionary(dict, key, value);
        free(key);
        free(value);

        token = strtok(NULL, "&");
    }

    return dict;
}

void handle_api_route(const char *url_payload) {
    Dictionary *params = parse_payload(url_payload);
    const char *name = get_from_dictionary(params, "name");
    if (name != NULL) {
        printf("Content-Type: application/json\r\n\r\n{\"name\": \"%s\"}\n", name);
    } else {
        printf("Content-Type: application/json\r\n\r\n{\"error\": \"Name parameter not found\"}\n");
    }
    free_dictionary(params);
}

int main() {
    // Simulate a CGI environment
    char *query_string = getenv("QUERY_STRING");

    if (query_string != NULL) {
        handle_api_route(query_string);
    } else {
        printf("Content-Type: application/json\r\n\r\n{\"error\": \"No payload\"}\n");
    }

    return 0;
}