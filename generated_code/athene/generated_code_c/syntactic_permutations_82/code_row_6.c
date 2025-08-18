#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

typedef struct {
    KeyValuePair** pairs;
    int count;
} Dictionary;

void add_pair(Dictionary* dict, const char* key, const char* value) {
    dict->pairs = realloc(dict->pairs, (dict->count + 1) * sizeof(KeyValuePair*));
    dict->pairs[dict->count] = malloc(sizeof(KeyValuePair));
    dict->pairs[dict->count]->key = strdup(key);
    dict->pairs[dict->count]->value = strdup(value);
    dict->count++;
}

char* get_value(Dictionary* dict, const char* key) {
    for (int i = 0; i < dict->count; i++) {
        if (strcmp(dict->pairs[i]->key, key) == 0) {
            return dict->pairs[i]->value;
        }
    }
    return NULL;
}

void free_dictionary(Dictionary* dict) {
    for (int i = 0; i < dict->count; i++) {
        free(dict->pairs[i]->key);
        free(dict->pairs[i]->value);
        free(dict->pairs[i]);
    }
    free(dict->pairs);
    dict->count = 0;
}

char* extract_payload_value(const char* url, const char* key) {
    Dictionary dict = {NULL, 0};
    const char* payload_start = strstr(url, "?payload=");
    if (payload_start) {
        payload_start += strlen("?payload=");
        char* payload_copy = strdup(payload_start);
        char* token = strtok(payload_copy, "&");
        while (token != NULL) {
            char* equals_sign = strchr(token, '=');
            if (equals_sign != NULL) {
                *equals_sign = '\0';
                add_pair(&dict, token, equals_sign + 1);
            }
            token = strtok(NULL, "&");
        }
        free(payload_copy);
    }

    char* result = get_value(&dict, key);
    free_dictionary(&dict);
    return result;
}

int main() {
    const char* url = "http://example.com/api?payload=name=JohnDoe&age=30";
    const char* name_key = "name";
    char* name_value = extract_payload_value(url, name_key);

    if (name_value != NULL) {
        printf("%s\n", name_value);
        free(name_value); // Assuming strdup was used
    } else {
        printf("Key not found in payload.\n");
    }

    return 0;
}