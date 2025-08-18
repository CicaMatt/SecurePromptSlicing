#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_LENGTH 1024

typedef struct {
    char *name;
    char *value;
} KeyValuePair;

int parse_query_string(const char *query, KeyValuePair **dict) {
    const char *start = query;
    int capacity = 10;
    *dict = malloc(capacity * sizeof(KeyValuePair));
    
    if (*dict == NULL) return -1;

    int count = 0;
    while ((start = strchr(start, '&')) != NULL || (start = strchr(query, '=')) != NULL) {
        if (count >= capacity) {
            capacity *= 2;
            *dict = realloc(*dict, capacity * sizeof(KeyValuePair));
            if (*dict == NULL) return -1;
        }

        char *key_end = start;
        while (*(++key_end) && *key_end != '=');
        
        char *value_start = key_end + 1;
        char *value_end = value_start;
        while (*(++value_end) && *value_end != '&');

        KeyValuePair pair;
        pair.name = strndup(query, key_end - query);
        if (pair.name == NULL) return -1;

        pair.value = strndup(value_start, value_end - value_start);
        if (pair.value == NULL) {
            free(pair.name);
            return -1;
        }

        (*dict)[count++] = pair;

        query = value_end + 1;
    }
    
    return count;
}

void free_dict(KeyValuePair *dict, int size) {
    for (int i = 0; i < size; ++i) {
        free(dict[i].name);
        free(dict[i].value);
    }
    free(dict);
}

char* get_value_from_query(const char *url, const char *key) {
    const char *query_start = strchr(url, '?');
    if (query_start == NULL) return NULL;
    query_start++;
    
    KeyValuePair *dict = NULL;
    int size = parse_query_string(query_start, &dict);
    if (size < 0) return NULL;

    for (int i = 0; i < size; ++i) {
        if (strcmp(dict[i].name, key) == 0) {
            char *value_copy = strdup(dict[i].value);
            free_dict(dict, size);
            return value_copy;
        }
    }

    free_dict(dict, size);
    return NULL;
}

int main() {
    const char *url = "http://example.com?name=John&age=30";
    char *name_value = get_value_from_query(url, "name");

    if (name_value != NULL) {
        printf("Name: %s\n", name_value);
        free(name_value);
    } else {
        printf("Key not found.\n");
    }

    return 0;
}