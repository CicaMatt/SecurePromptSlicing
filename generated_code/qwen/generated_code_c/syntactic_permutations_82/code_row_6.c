#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair **pairs;
    int count;
} Dictionary;

Dictionary* createDictionary() {
    Dictionary *dict = malloc(sizeof(Dictionary));
    dict->count = 0;
    dict->pairs = NULL;
    return dict;
}

void addToDictionary(Dictionary *dict, const char *key, const char *value) {
    KeyValuePair *pair = malloc(sizeof(KeyValuePair));
    pair->key = strdup(key);
    pair->value = strdup(value);

    dict->count++;
    dict->pairs = realloc(dict->pairs, sizeof(KeyValuePair*) * dict->count);
    dict->pairs[dict->count - 1] = pair;
}

char* getValueFromDictionary(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->count; i++) {
        if (strcmp(dict->pairs[i]->key, key) == 0) {
            return dict->pairs[i]->value;
        }
    }
    return NULL;
}

void freeDictionary(Dictionary *dict) {
    for (int i = 0; i < dict->count; i++) {
        free(dict->pairs[i]->key);
        free(dict->pairs[i]->value);
        free(dict->pairs[i]);
    }
    free(dict->pairs);
    free(dict);
}

char* extractPayload(const char *url) {
    const char *queryStart = strchr(url, '?');
    if (queryStart == NULL) return NULL;

    const char *keyValueStart = strstr(queryStart, "payload=");
    if (keyValueStart == NULL) return NULL;
    
    keyValueStart += 8; // Move past "payload="

    const char *end = strchr(keyValueStart, '&');
    if (end != NULL) {
        int length = end - keyValueStart;
        char *result = malloc(length + 1);
        strncpy(result, keyValueStart, length);
        result[length] = '\0';
        return result;
    }

    // If no '&' found, take the rest of the string
    return strdup(keyValueStart);
}

void parsePayload(Dictionary *dict, const char *payload) {
    if (payload == NULL || strlen(payload) == 0) return;

    char *copy = strdup(payload);
    char *token = strtok(copy, "&");
    while (token != NULL) {
        char *key = strtok(token, "=");
        char *value = strtok(NULL, "=");
        if (key != NULL && value != NULL) {
            addToDictionary(dict, key, value);
        }
        token = strtok(NULL, "&");
    }
    free(copy);
}

int main() {
    const char *url = "http://example.com/api?payload=name=John&age=30";
    
    char *payload = extractPayload(url);
    if (payload == NULL) {
        printf("No payload found\n");
        return 1;
    }

    Dictionary *dict = createDictionary();
    parsePayload(dict, payload);

    char *name = getValueFromDictionary(dict, "name");
    if (name != NULL) {
        printf("%s\n", name);
    } else {
        printf("Name not found in payload\n");
    }

    free(payload);
    freeDictionary(dict);

    return 0;
}