#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REQUEST_PATH "/api"
#define PARAMETER_NAME "payload"

typedef struct {
    char *name;
    char *value;
} KeyValuePair;

typedef struct {
    size_t count;
    KeyValuePair *pairs;
} Dictionary;

Dictionary* load_payload(const char *payload) {
    if (payload == NULL || strlen(payload) == 0) return NULL;

    Dictionary *dict = malloc(sizeof(Dictionary));
    dict->count = 0;
    dict->pairs = malloc(10 * sizeof(KeyValuePair)); // Initial capacity

    size_t len = strlen(payload);
    char *token = strtok((char *)payload, "&");
    while (token != NULL) {
        if (dict->count >= 10) { // Resize array if needed
            dict->pairs = realloc(dict->pairs, (dict->count + 10) * sizeof(KeyValuePair));
        }

        char *key_value = strdup(token);
        char *equal_sign = strchr(key_value, '=');
        if (equal_sign != NULL) {
            *equal_sign = '\0';
            KeyValuePair pair;
            pair.name = strdup(strtok(key_value, "="));
            pair.value = equal_sign + 1; // Move past the '='
            dict->pairs[dict->count++] = pair;
        }

        free(key_value);
        token = strtok(NULL, "&");
    }
    return dict;
}

char* get_name_value(Dictionary *dict) {
    for (size_t i = 0; i < dict->count; ++i) {
        if (strcmp(dict->pairs[i].name, PARAMETER_NAME) == 0) {
            return dict->pairs[i].value;
        }
    }
    return NULL;
}

void free_dictionary(Dictionary *dict) {
    for (size_t i = 0; i < dict->count; ++i) {
        free(dict->pairs[i].name);
    }
    free(dict->pairs);
    free(dict);
}

int main(int argc, char *argv[]) {
    if (argc != 2 || strcmp(argv[1], REQUEST_PATH) != 0) {
        printf("Invalid request path.\n");
        return 1;
    }

    const char *payload = getenv("QUERY_STRING");

    Dictionary *dict = load_payload(payload);
    if (dict == NULL) {
        printf("No valid payload found.\n");
        return 1;
    }

    char *name_value = get_name_value(dict);
    if (name_value != NULL) {
        printf("%s\n", name_value);
    } else {
        printf("Parameter 'payload' not found in URL.\n");
    }

    free_dictionary(dict);
    return 0;
}