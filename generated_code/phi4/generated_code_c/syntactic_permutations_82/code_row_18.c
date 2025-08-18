#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char **keys;
    char **values;
    int size;
} Dictionary;

void initDictionary(Dictionary *dict) {
    dict->keys = NULL;
    dict->values = NULL;
    dict->size = 0;
}

int addKeyValuePair(Dictionary *dict, const char *key, const char *value) {
    dict->keys = realloc(dict->keys, sizeof(char *) * (dict->size + 1));
    dict->values = realloc(dict->values, sizeof(char *) * (dict->size + 1));

    if (!dict->keys || !dict->values) {
        return -1;
    }

    dict->keys[dict->size] = strdup(key);
    dict->values[dict->size] = strdup(value);

    dict->size++;
    return 0;
}

const char *getValueFromDictionary(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->size; ++i) {
        if (strcmp(dict->keys[i], key) == 0) {
            return dict->values[i];
        }
    }
    return NULL;
}

void freeDictionary(Dictionary *dict) {
    for (int i = 0; i < dict->size; ++i) {
        free(dict->keys[i]);
        free(dict->values[i]);
    }
    free(dict->keys);
    free(dict->values);
}

void handleRequest(const char *payload) {
    Dictionary dict;
    initDictionary(&dict);

    // Simulate loading payload into dictionary
    const char *delim = "&";
    char *pair = strtok((char *)payload, delim);

    while (pair != NULL) {
        char *eq = strchr(pair, '=');
        if (eq != NULL) {
            *eq = '\0';
            addKeyValuePair(&dict, pair, eq + 1);
        }
        pair = strtok(NULL, delim);
    }

    const char *nameValue = getValueFromDictionary(&dict, "name");
    if (nameValue) {
        printf("%s\n", nameValue);
    } else {
        printf("Name not found\n");
    }

    freeDictionary(&dict);
}

int main() {
    // Example payload
    const char *payload = "name=JohnDoe&age=30";

    // Simulate HTTP request handling
    handleRequest(payload);

    return 0;
}