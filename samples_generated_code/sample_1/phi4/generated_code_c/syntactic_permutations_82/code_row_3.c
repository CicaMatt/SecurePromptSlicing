#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    size_t count;
} Dictionary;

void parse_query(const char *query, Dictionary *dict) {
    const char *start = query;
    const char *end;
    char key[BUFFER_SIZE];
    char value[BUFFER_SIZE];

    while (*start) {
        // Find key
        end = strchr(start, '=');
        if (!end || end - start >= BUFFER_SIZE) break;
        strncpy(key, start, end - start);
        key[end - start] = '\0';
        start = end + 1;

        // Find value
        end = strchr(start, '&');
        if (!end || start == end) break;
        strncpy(value, start, end - start);
        value[end - start] = '\0';

        // Add to dictionary
        dict->pairs = realloc(dict->pairs, (dict->count + 1) * sizeof(KeyValuePair));
        dict->pairs[dict->count].key = strdup(key);
        dict->pairs[dict->count].value = strdup(value);
        dict->count++;

        start = end + 1;
    }
}

const char* get_value_from_dict(Dictionary *dict, const char *name) {
    for (size_t i = 0; i < dict->count; ++i) {
        if (strcmp(dict->pairs[i].key, name) == 0) {
            return dict->pairs[i].value;
        }
    }
    return NULL;
}

void free_dict(Dictionary *dict) {
    for (size_t i = 0; i < dict->count; ++i) {
        free((void*)dict->pairs[i].key);
        free((void*)dict->pairs[i].value);
    }
    free(dict->pairs);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *url = argv[1];
    const char *query_start = strchr(url, '?');
    if (!query_start) {
        fprintf(stderr, "No query parameters found in URL.\n");
        return EXIT_FAILURE;
    }
    query_start++; // Move past the '?' character

    Dictionary dict = {NULL, 0};
    parse_query(query_start, &dict);

    const char *name_value = get_value_from_dict(&dict, "payload");

    if (name_value) {
        printf("Name value from dictionary: %s\n", name_value);
    } else {
        printf("Payload not found in URL parameters.\n");
    }

    free_dict(&dict);
    return EXIT_SUCCESS;
}