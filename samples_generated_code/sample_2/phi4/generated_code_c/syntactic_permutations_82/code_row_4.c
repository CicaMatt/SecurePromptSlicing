#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    size_t size;
    KeyValuePair *pairs;
} Dictionary;

void add_to_dictionary(Dictionary *dict, const char *key, const char *value) {
    dict->size++;
    dict->pairs = realloc(dict->pairs, sizeof(KeyValuePair) * dict->size);
    if (!dict->pairs) {
        perror("Unable to allocate memory");
        exit(EXIT_FAILURE);
    }
    KeyValuePair pair;
    pair.key = strdup(key);
    pair.value = strdup(value);
    dict->pairs[dict->size - 1] = pair;
}

char* get_value_from_dictionary(Dictionary *dict, const char *key) {
    for (size_t i = 0; i < dict->size; ++i) {
        if (strcmp(dict->pairs[i].key, key) == 0) {
            return dict->pairs[i].value;
        }
    }
    return NULL;
}

void free_dictionary(Dictionary *dict) {
    for (size_t i = 0; i < dict->size; ++i) {
        free(dict->pairs[i].key);
        free(dict->pairs[i].value);
    }
    free(dict->pairs);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s /api?payload={\"name\":\"John Doe\"}\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *route = argv[1];
    if (strncmp(route, "/api?", 5) == 0) {
        const char *payload_str = route + 5;
        Dictionary dict = { .size = 0, .pairs = NULL };

        // Extract payload from URL
        size_t len = strlen(payload_str);
        char buffer[BUFFER_SIZE];
        snprintf(buffer, BUFFER_SIZE, "{\"%s\"", strchr(payload_str, '{') + 1);

        char *name_key = strstr(buffer, "\"name\":\"");
        if (name_key) {
            name_key += strlen("\"name\":\"");
            char *end_quote = strchr(name_key, '"');
            if (end_quote) {
                *end_quote = '\0';
                add_to_dictionary(&dict, "name", name_key);
            }
        }

        // Return the value for key 'name'
        char *name_value = get_value_from_dictionary(&dict, "name");
        if (name_value) {
            printf("Name: %s\n", name_value);
        } else {
            printf("Name not found in payload.\n");
        }

        free_dictionary(&dict);
    } else {
        fprintf(stderr, "Invalid route. Use /api?\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}