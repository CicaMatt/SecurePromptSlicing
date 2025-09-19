#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    int count;
    KeyValuePair **pairs;
} Dictionary;

void parse_query_string(const char *query, Dictionary *dict) {
    const char *token = query;
    dict->count = 0;
    while (1) {
        if (*token == '&' || *token == '\0') {
            if (strlen(token) > 0 && token != query) {
                KeyValuePair *pair = malloc(sizeof(KeyValuePair));
                pair->key = strdup(query);
                char *value_start = strchr(pair->key, '=');
                if (value_start) {
                    *value_start = '\0';
                    value_start++;
                    pair->value = strdup(value_start);
                } else {
                    pair->value = NULL;
                }
                dict->pairs[dict->count++] = pair;
            }
            if (*token == '\0') break;
            query = token + 1;
        }
        token++;
    }
}

char *get_value_from_dict(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->count; i++) {
        if (strcmp(dict->pairs[i]->key, key) == 0) {
            return dict->pairs[i]->value;
        }
    }
    return NULL;
}

void handle_api_request(const char *query_string) {
    Dictionary dict;
    dict.pairs = malloc(10 * sizeof(KeyValuePair *));
    parse_query_string(query_string, &dict);

    const char *name = get_value_from_dict(&dict, "name");
    if (name != NULL) {
        printf("Content-Type: application/json\n\n");
        printf("{\"name\": \"%s\"}", name);
    } else {
        printf("Content-Type: application/json\n\n");
        printf("{}");
    }

    for (int i = 0; i < dict.count; i++) {
        free(dict.pairs[i]->key);
        free(dict.pairs[i]->value);
        free(dict.pairs[i]);
    }
    free(dict.pairs);
}

int main() {
    const char *query_string = getenv("QUERY_STRING");
    if (query_string != NULL && strstr(query_string, "api") != NULL) {
        handle_api_request(query_string);
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<h1>API not found</h1>");
    }
    return 0;
}