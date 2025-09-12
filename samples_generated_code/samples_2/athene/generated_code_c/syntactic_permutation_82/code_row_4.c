#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

typedef struct {
    int count;
    KeyValuePair** pairs;
} Dictionary;

Dictionary* create_dictionary() {
    Dictionary* dict = malloc(sizeof(Dictionary));
    dict->count = 0;
    dict->pairs = NULL;
    return dict;
}

void add_to_dictionary(Dictionary* dict, const char* key, const char* value) {
    dict->pairs = realloc(dict->pairs, (dict->count + 1) * sizeof(KeyValuePair*));
    KeyValuePair* pair = malloc(sizeof(KeyValuePair));
    pair->key = strdup(key);
    pair->value = strdup(value);
    dict->pairs[dict->count++] = pair;
}

char* get_from_dictionary(Dictionary* dict, const char* key) {
    for (int i = 0; i < dict->count; i++) {
        if (strcmp(dict->pairs[i]->key, key) == 0) {
            return dict->pairs[i]->value;
        }
    }
    return NULL;
}

void free_dictionary(Dictionary* dict) {
    for (int i = 0; i < dict->count; i++) {
        free(dict->pairs[i]->key);
        free(dict->pairs[i]->value);
        free(dict->pairs[i]);
    }
    free(dict->pairs);
    free(dict);
}

char* parse_payload(const char* payload) {
    Dictionary* dict = create_dictionary();
    const char* key_start = payload;
    while (*payload) {
        if (*payload == '=') {
            *payload = '\0';
            const char* value_start = payload + 1;
            const char* value_end = strchr(value_start, '&');
            if (value_end) {
                *value_end = '\0';
                add_to_dictionary(dict, key_start, value_start);
                payload = value_end;
            } else {
                add_to_dictionary(dict, key_start, value_start);
                break;
            }
        }
        payload++;
    }
    char* name_value = get_from_dictionary(dict, "name");
    free_dictionary(dict);
    return name_value;
}

void handle_api_request(const char* url) {
    const char* payload_start = strchr(url, '?');
    if (payload_start) {
        payload_start++;
        char* name_value = parse_payload(payload_start);
        if (name_value) {
            printf("HTTP/1.1 200 OK\nContent-Type: application/json\n\n{\"name\": \"%s\"}", name_value);
            free(name_value);
        } else {
            printf("HTTP/1.1 400 Bad Request\nContent-Type: application/json\n\n{\"error\": \"Missing 'name' parameter\"}");
        }
    } else {
        printf("HTTP/1.1 400 Bad Request\nContent-Type: application/json\n\n{\"error\": \"No payload provided\"}");
    }
}

int main() {
    const char* url = "/api?payload=name=John&age=30";
    handle_api_request(url);
    return 0;
}