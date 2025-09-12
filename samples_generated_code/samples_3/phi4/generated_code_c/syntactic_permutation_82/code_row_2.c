#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A simple JSON parser for demonstration purposes.
typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    size_t length;
    KeyValuePair *pairs;
} JsonDict;

JsonDict parse_json(const char *json) {
    JsonDict dict = {0, NULL};
    const char *start = json;
    size_t num_pairs = 1; // Count of pairs including the last one
    while (*start) {
        if (*start == '{') start++;
        while (*start && *start != '}') {
            if (*start == '"') {
                start++; // Skip opening quote

                char *key_start = (char *)start;
                while (*start && *start != '"') start++;
                size_t key_len = start - key_start;
                char *key = strndup(key_start, key_len);

                start += 2; // Skip closing quote and ':'

                if (*start == '"') {
                    start++; // Skip opening quote
                    char *value_start = (char *)start;
                    while (*start && *start != '"') start++;
                    size_t value_len = start - value_start;
                    char *value = strndup(value_start, value_len);

                    start += 2; // Skip closing quote and ',' or '}'
                    if (*start == ',') {
                        start++; // Skip comma
                    }

                    num_pairs++;

                    dict.length++;
                    dict.pairs = realloc(dict.pairs, sizeof(KeyValuePair) * dict.length);
                    KeyValuePair pair = {key, value};
                    dict.pairs[dict.length - 1] = pair;
                }
            } else if (*start == '}') {
                break;
            } else {
                start++;
            }
        }

        if (*start == '}') {
            start++; // Skip closing brace
        }
    }
    return dict;
}

void free_json_dict(JsonDict *dict) {
    for (size_t i = 0; i < dict->length; i++) {
        free(dict->pairs[i].key);
        free(dict->pairs[i].value);
    }
    free(dict->pairs);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s '<json_payload>'\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *payload = argv[1];
    JsonDict dict = parse_json(payload);

    for (size_t i = 0; i < dict.length; i++) {
        if (strcmp(dict.pairs[i].key, "name") == 0) {
            printf("Name: %s\n", dict.pairs[i].value);
            free_json_dict(&dict);
            return EXIT_SUCCESS;
        }
    }

    printf("Key 'name' not found.\n");
    free_json_dict(&dict);
    return EXIT_FAILURE;
}