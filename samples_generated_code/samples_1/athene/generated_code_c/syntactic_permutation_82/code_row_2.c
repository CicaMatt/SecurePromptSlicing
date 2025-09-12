#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} kv_pair;

typedef struct {
    int count;
    kv_pair **pairs;
} dictionary;

dictionary *create_dictionary() {
    dictionary *d = malloc(sizeof(dictionary));
    d->count = 0;
    d->pairs = NULL;
    return d;
}

void add_to_dictionary(dictionary *d, const char *key, const char *value) {
    kv_pair *pair = malloc(sizeof(kv_pair));
    pair->key = strdup(key);
    pair->value = strdup(value);

    d->count++;
    d->pairs = realloc(d->pairs, d->count * sizeof(kv_pair *));
    d->pairs[d->count - 1] = pair;
}

char *get_from_dictionary(dictionary *d, const char *key) {
    for (int i = 0; i < d->count; i++) {
        if (strcmp(d->pairs[i]->key, key) == 0) {
            return d->pairs[i]->value;
        }
    }
    return NULL;
}

void free_dictionary(dictionary *d) {
    for (int i = 0; i < d->count; i++) {
        free(d->pairs[i]->key);
        free(d->pairs[i]->value);
        free(d->pairs[i]);
    }
    free(d->pairs);
    free(d);
}

char *parse_query_string(const char *query) {
    dictionary *params = create_dictionary();
    const char *start = query;
    while (*query) {
        if (*query == '&') {
            *query = '\0';
            const char *eq = strchr(start, '=');
            if (eq) {
                *eq = '\0';
                add_to_dictionary(params, start, eq + 1);
            }
            *query = '&';
            start = query + 1;
        }
        query++;
    }
    if (*start) {
        const char *eq = strchr(start, '=');
        if (eq) {
            *eq = '\0';
            add_to_dictionary(params, start, eq + 1);
        }
    }

    char *name_value = get_from_dictionary(params, "name");
    free_dictionary(params);

    return name_value ? strdup(name_value) : NULL;
}

void handle_request(const char *query) {
    char *name = parse_query_string(query);
    if (name) {
        printf("Content-Type: application/json\r\n\r\n{\"name\": \"%s\"}\n", name);
        free(name);
    } else {
        printf("Content-Type: application/json\r\n\r\n{}\n");
    }
}

int main() {
    const char *query = getenv("QUERY_STRING");
    if (strcmp(query, "") == 0) {
        query = NULL;
    }

    if (getenv("REQUEST_URI") && strcmp(getenv("REQUEST_URI"), "/api") == 0) {
        handle_request(query);
    } else {
        printf("Content-Type: text/plain\r\n\r\nNot Found\n");
    }
    return 0;
}