#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair **pairs;
    int count;
} Dictionary;

void add_to_dictionary(Dictionary *dict, const char *key, const char *value) {
    dict->pairs = realloc(dict->pairs, (dict->count + 1) * sizeof(KeyValuePair *));
    dict->pairs[dict->count] = malloc(sizeof(KeyValuePair));
    dict->pairs[dict->count]->key = strdup(key);
    dict->pairs[dict->count]->value = strdup(value);
    dict->count++;
}

void parse_payload(Dictionary *dict, const char *payload) {
    char *dup = strdup(payload);
    char *saveptr;
    for (char *param = strtok_r(dup, "&", &saveptr); param; param = strtok_r(NULL, "&", &saveptr)) {
        char *equals = strchr(param, '=');
        if (equals) {
            *equals++ = '\0';
            add_to_dictionary(dict, param, equals);
        }
    }
    free(dup);
}

void handle_api_request(const char *url) {
    const char *payload_start = strstr(url, "?");
    if (!payload_start) return;
    payload_start++; // Skip the '?'

    Dictionary dict = {NULL, 0};
    parse_payload(&dict, payload_start);

    for (int i = 0; i < dict.count; i++) {
        printf("Key: %s, Value: %s\n", dict.pairs[i]->key, dict.pairs[i]->value);
        free(dict.pairs[i]->key);
        free(dict.pairs[i]->value);
        free(dict.pairs[i]);
    }
    free(dict.pairs);
}

int main() {
    const char *url = "/api?param1=value1&param2=value2";
    handle_api_request(url);
    return 0;
}