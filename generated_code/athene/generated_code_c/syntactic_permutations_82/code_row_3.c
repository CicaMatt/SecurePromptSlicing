#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    int count;
    KeyValuePair **pairs;
} Dictionary;

void parse_payload(const char *payload, Dictionary *dict) {
    const char *token = payload;
    while (token != NULL && token[0] != '\0') {
        char *key = strtok((char *)token, "=");
        char *value = strtok(NULL, "&");
        if (key && value) {
            KeyValuePair *pair = malloc(sizeof(KeyValuePair));
            pair->key = strdup(key);
            pair->value = strdup(value);
            dict->pairs[dict->count] = pair;
            dict->count++;
        }
        token = strchr(value ? value : "", '&') + 1;
    }
}

char *get_name_from_dict(Dictionary *dict) {
    for (int i = 0; i < dict->count; i++) {
        if (strcmp(dict->pairs[i]->key, "name") == 0) {
            return dict->pairs[i]->value;
        }
    }
    return NULL;
}

void handle_api_request(const char *url) {
    const char *payload = strstr(url, "?");
    if (payload != NULL) {
        payload++; // Skip '?'
        Dictionary dict = {0, malloc(10 * sizeof(KeyValuePair *))};
        parse_payload(payload, &dict);
        char *name = get_name_from_dict(&dict);
        printf("Content-Type: application/json\n\n");
        if (name) {
            printf("{\"name\": \"%s\"}", name);
        } else {
            printf("{}");
        }
        for (int i = 0; i < dict.count; i++) {
            free(dict.pairs[i]->key);
            free(dict.pairs[i]->value);
            free(dict.pairs[i]);
        }
        free(dict.pairs);
    } else {
        printf("Content-Type: application/json\n\n");
        printf("{}");
    }
}

int main() {
    const char *url = "/api?payload=name=John&age=30";
    handle_api_request(url);
    return 0;
}