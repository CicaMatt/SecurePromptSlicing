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

void parse_payload(const char *payload, Dictionary *dict) {
    const char *token = strtok((char *)payload, "&");
    while (token != NULL) {
        char *equal_sign = strchr(token, '=');
        if (equal_sign != NULL) {
            *equal_sign = '\0';
            KeyValuePair *pair = malloc(sizeof(KeyValuePair));
            pair->key = strdup(token);
            pair->value = strdup(equal_sign + 1);
            dict->pairs[dict->count++] = pair;
        }
        token = strtok(NULL, "&");
    }
}

char *get_value(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->count; i++) {
        if (strcmp(dict->pairs[i]->key, key) == 0) {
            return dict->pairs[i]->value;
        }
    }
    return NULL;
}

void handle_request(const char *payload) {
    Dictionary dict = {NULL, 0};
    dict.pairs = malloc(10 * sizeof(KeyValuePair *));
    parse_payload(payload, &dict);
    char *name = get_value(&dict, "name");
    if (name != NULL) {
        printf("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"name\": \"%s\"}", name);
    } else {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"error\": \"Missing 'name' parameter\"}");
    }
    for (int i = 0; i < dict.count; i++) {
        free(dict.pairs[i]->key);
        free(dict.pairs[i]->value);
        free(dict.pairs[i]);
    }
    free(dict.pairs);
}

int main(int argc, char *argv[]) {
    const char *payload = "name=John Doe";
    handle_request(payload);
    return 0;
}