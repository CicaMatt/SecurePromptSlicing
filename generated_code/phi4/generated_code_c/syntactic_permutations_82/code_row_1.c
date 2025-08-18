#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char **keys;
    char **values;
    size_t count;
} Dictionary;

Dictionary* create_dictionary() {
    Dictionary *dict = malloc(sizeof(Dictionary));
    dict->keys = NULL;
    dict->values = NULL;
    dict->count = 0;
    return dict;
}

void free_dictionary(Dictionary *dict) {
    for (size_t i = 0; i < dict->count; i++) {
        free(dict->keys[i]);
        free(dict->values[i]);
    }
    free(dict->keys);
    free(dict->values);
    free(dict);
}

int add_to_dictionary(Dictionary *dict, const char *key, const char *value) {
    size_t new_count = dict->count + 1;
    dict->keys = realloc(dict->keys, sizeof(char*) * new_count);
    dict->values = realloc(dict->values, sizeof(char*) * new_count);

    if (dict->keys == NULL || dict->values == NULL) {
        return -1; // Memory allocation failed
    }

    dict->keys[dict->count] = strdup(key);
    dict->values[dict->count] = strdup(value);
    dict->count++;
    return 0;
}

char* get_value_from_dictionary(Dictionary *dict, const char *key) {
    for (size_t i = 0; i < dict->count; i++) {
        if (strcmp(dict->keys[i], key) == 0) {
            return dict->values[i];
        }
    }
    return NULL;
}

int main(int argc, char **argv) {
    if (argc != 2 || strcmp(argv[1], "/api") != 0) {
        printf("Usage: %s /api?payload=%s\n", argv[0], "key1=value1&key2=value2");
        return 1;
    }

    const char *query_string = getenv("QUERY_STRING");
    if (query_string == NULL || strstr(query_string, "payload=") == NULL) {
        printf("{\"error\":\"No payload parameter found\"}\n");
        return 1;
    }

    Dictionary *dict = create_dictionary();
    const char *payload_str = query_string + strlen("payload=");
    char payload[MAX_PAYLOAD_SIZE];
    strncpy(payload, payload_str, MAX_PAYLOAD_SIZE - 1);
    payload[MAX_PAYLOAD_SIZE - 1] = '\0';

    char *token = strtok(payload, "&");
    while (token != NULL) {
        const char *separator = strchr(token, '=');
        if (separator == NULL) {
            token = strtok(NULL, "&");
            continue;
        }

        *separator = '\0';
        add_to_dictionary(dict, strdup(token), strdup(separator + 1));
        token = strtok(NULL, "&");
    }

    char *name_value = get_value_from_dictionary(dict, "name");
    if (name_value != NULL) {
        printf("{\"name\":\"%s\"}\n", name_value);
    } else {
        printf("{\"error\":\"Name parameter not found in payload\"}\n");
    }

    free_dictionary(dict);
    return 0;
}