#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char *name;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    size_t count;
} Dictionary;

Dictionary* create_dictionary() {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    dict->pairs = NULL;
    dict->count = 0;
    return dict;
}

void free_dictionary(Dictionary *dict) {
    for (size_t i = 0; i < dict->count; i++) {
        free(dict->pairs[i].name);
        free(dict->pairs[i].value);
    }
    free(dict->pairs);
    free(dict);
}

KeyValuePair* find_key(Dictionary *dict, const char *key) {
    for (size_t i = 0; i < dict->count; i++) {
        if (strcmp(dict->pairs[i].name, key) == 0) {
            return &dict->pairs[i];
        }
    }
    return NULL;
}

void add_to_dictionary(Dictionary *dict, const char *key, const char *value) {
    KeyValuePair new_pair = {strdup(key), strdup(value)};
    dict->count++;
    dict->pairs = (KeyValuePair *)realloc(dict->pairs, sizeof(KeyValuePair) * dict->count);
    dict->pairs[dict->count - 1] = new_pair;
}

char* get_request_payload(const char *url) {
    const char *payload_start = "payload=";
    size_t start_pos = strlen(url) - strlen(payload_start);

    if (start_pos == 0) return NULL;

    for (size_t i = start_pos; i < strlen(url); i++) {
        if (url[i] == '&') {
            start_pos = i;
            break;
        }
    }

    if (start_pos == strlen(url)) return NULL;

    size_t payload_length = strlen(url) - start_pos - 1;
    char *payload = (char *)malloc(payload_length + 1);
    strncpy(payload, url + start_pos + 1, payload_length);
    payload[payload_length] = '\0';

    return payload;
}

int main() {
    const char *url = "http://example.com/api?name=John&age=30";
    char *payload = get_request_payload(url);

    if (payload == NULL) {
        printf("No payload found.\n");
        return 1;
    }

    Dictionary *dict = create_dictionary();
    char *token = strtok(payload, "&");

    while (token != NULL) {
        char *key_value = strdup(token);
        char *equals_sign = strchr(key_value, '=');

        if (equals_sign == NULL) {
            free(key_value);
            token = strtok(NULL, "&");
            continue;
        }

        *equals_sign = '\0';
        add_to_dictionary(dict, key_value, equals_sign + 1);

        free(key_value);
        token = strtok(NULL, "&");
    }

    KeyValuePair *name_pair = find_key(dict, "name");

    if (name_pair != NULL) {
        printf("Name: %s\n", name_pair->value);
    } else {
        printf("Name not found.\n");
    }

    free_dictionary(dict);
    free(payload);

    return 0;
}