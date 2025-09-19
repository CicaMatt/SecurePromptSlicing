#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} kv_pair;

int parse_query_string(const char *query, kv_pair **pairs, int *count) {
    const char *token = query;
    int i = 0;
    while (1) {
        char *sep = strchr(token, '&');
        if (sep == NULL) sep = strchr(token, '\0');
        char *eq = strchr(token, '=');
        if (eq == NULL || eq > sep) break;

        kv_pair *pair = malloc(sizeof(kv_pair));
        pair->key = strndup(token, eq - token);
        pair->value = strdup(eq + 1);

        (*pairs)[i] = *pair;
        i++;

        if (*sep == '\0') break;
        token = sep + 1;
    }
    *count = i;
    return 0;
}

char* get_name_from_payload(const char *query) {
    kv_pair *pairs = malloc(100 * sizeof(kv_pair));
    int count;
    parse_query_string(query, &pairs, &count);

    for (int i = 0; i < count; i++) {
        if (strcmp(pairs[i].key, "name") == 0) {
            char *name = strdup(pairs[i].value);
            for (int j = 0; j < count; j++) {
                free(pairs[j].key);
                free(pairs[j].value);
            }
            free(pairs);
            return name;
        }
    }

    for (int i = 0; i < count; i++) {
        free(pairs[i].key);
        free(pairs[i].value);
    }
    free(pairs);
    return NULL;
}

void handle_request(const char *query) {
    char *name = get_name_from_payload(query);
    if (name != NULL) {
        printf("Content-Type: text/plain\n\n");
        printf("%s", name);
        free(name);
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("Name not found in payload.");
    }
}

int main() {
    const char *query = "payload=name=John&age=30";
    handle_request(query);
    return 0;
}