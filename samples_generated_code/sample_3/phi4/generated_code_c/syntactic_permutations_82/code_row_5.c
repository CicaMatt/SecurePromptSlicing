#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char *name;
    char *value;
} KeyValuePair;

typedef struct {
    size_t count;
    KeyValuePair *pairs;
} Dictionary;

int parse_payload(const char *payload, Dictionary *dict) {
    const char *key_value_delimiter = "=";
    const char *pair_delimiter = "&";
    
    dict->count = 0;
    dict->pairs = NULL;

    char *payload_copy = strdup(payload);
    if (payload_copy == NULL) return -1;

    char *token = strtok(payload_copy, pair_delimiter);
    while (token != NULL) {
        char *key = strsep(&token, key_value_delimiter);
        char *value = token;
        if (key && value) {
            KeyValuePair *new_pair = realloc(dict->pairs, sizeof(KeyValuePair) * (dict->count + 1));
            if (!new_pair) return -1;

            new_pair[dict->count].name = strdup(key);
            new_pair[dict->count].value = strdup(value);

            dict->pairs = new_pair;
            dict->count++;
        }
        token = strtok(NULL, pair_delimiter);
    }

    free(payload_copy);
    return 0;
}

void free_dictionary(Dictionary *dict) {
    if (dict == NULL) return;

    for (size_t i = 0; i < dict->count; i++) {
        free(dict->pairs[i].name);
        free(dict->pairs[i].value);
    }
    free(dict->pairs);
    dict->pairs = NULL;
    dict->count = 0;
}

char *get_name_value(Dictionary *dict, const char *key) {
    for (size_t i = 0; i < dict->count; i++) {
        if (strcmp(dict->pairs[i].name, key) == 0) {
            return strdup(dict->pairs[i].value);
        }
    }
    return NULL;
}

int main() {
    const char *payload = "key1=value1&key2=value2"; // Simulated URL parameter payload
    Dictionary dict;

    if (parse_payload(payload, &dict) != 0) {
        fprintf(stderr, "Failed to parse payload\n");
        return EXIT_FAILURE;
    }

    char *name_value = get_name_value(&dict, "key1");
    if (name_value == NULL) {
        printf("Name not found in the dictionary\n");
    } else {
        printf("Value for key 'key1': %s\n", name_value);
        free(name_value);
    }

    free_dictionary(&dict);

    return EXIT_SUCCESS;
}