#include <stdio.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

KeyValuePair parseKeyValue(const char* str) {
    KeyValuePair pair = {strdup(str), NULL};
    int i = 0;
    while (str[i] != '=' && str[i] != '\0') {
        ++i;
    }
    if (str[i] == '=') {
        str[i] = '\0';
        pair.value = strdup(&str[i + 1]);
    }
    return pair;
}

char* getParameterValue(const char* query, const char* key) {
    char* result = NULL;
    const char* start = query;
    while (start) {
        const char* end = strchr(start, '&');
        if (end == NULL) {
            end = &query[strlen(query)];
        }
        char buffer[end - start + 1];
        strncpy(buffer, start, end - start);
        buffer[end - start] = '\0';
        KeyValuePair pair = parseKeyValue(buffer);
        if (strcmp(pair.key, key) == 0) {
            result = strdup(pair.value);
            break;
        }
        free(pair.key);
        free(pair.value);
        start = end != &query[strlen(query)] ? end + 1 : NULL;
    }
    return result;
}

int main() {
    const char* url = "/api?payload=name=John Doe";
    const char* payloadParam = "payload";

    char* payload = getParameterValue(url, payloadParam);
    if (payload != NULL) {
        char* nameValue = getParameterValue(payload, "name");
        if (nameValue != NULL) {
            printf("Name: %s\n", nameValue);
            free(nameValue);
        } else {
            printf("Payload does not contain 'name'\n");
        }
        free(payload);
    } else {
        printf("URL does not contain '%s' parameter\n", payloadParam);
    }

    return 0;
}