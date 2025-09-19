#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

void parse_query_string(const char *query, KeyValuePair **dict, int *size) {
    const char *start = query;
    const char *end = NULL;
    *dict = malloc(MAX_PAYLOAD_SIZE * sizeof(KeyValuePair));
    *size = 0;

    while ((end = strchr(start, '&'))) {
        size_t len = end - start;
        KeyValuePair pair;
        pair.key = strndup(start, len);
        start += len + 1; // Move past the '&'
        
        end = strchr(start, '=');
        if (end) {
            char *value_start = ++end;
            while (*value_start == ' ') value_start++; // Skip leading spaces in value
            size_t value_len = strlen(value_start);

            pair.value = strndup(value_start, value_len);
            start += value_len + 1; // Move past the '=' and value

            (*dict)[(*size)++] = pair;
        }
    }

    if (*start) {
        KeyValuePair pair;
        end = strchr(start, '=');
        if (end) {
            char *value_start = ++end;
            while (*value_start == ' ') value_start++; // Skip leading spaces in value
            size_t value_len = strlen(value_start);

            pair.key = strdup(start);
            pair.value = strndup(value_start, value_len);
            (*dict)[(*size)++] = pair;
        }
    }
}

char* get_value_from_dict(KeyValuePair *dict, int size, const char *key) {
    for (int i = 0; i < size; ++i) {
        if (strcmp(dict[i].key, key) == 0) {
            return dict[i].value;
        }
    }
    return NULL;
}

void free_dictionary(KeyValuePair *dict, int size) {
    for (int i = 0; i < size; ++i) {
        free((void *)dict[i].key);
        free((void *)dict[i].value);
    }
    free(dict);
}

int main() {
    char payload[MAX_PAYLOAD_SIZE] = "name=John&age=30&city=New%20York";
    KeyValuePair *dictionary;
    int size;

    parse_query_string(payload, &dictionary, &size);

    const char *key_to_find = "name";
    char *value = get_value_from_dict(dictionary, size, key_to_find);

    if (value) {
        printf("Value for '%s': %s\n", key_to_find, value);
    } else {
        printf("Key '%s' not found.\n", key_to_find);
    }

    free_dictionary(dictionary, size);
    return 0;
}