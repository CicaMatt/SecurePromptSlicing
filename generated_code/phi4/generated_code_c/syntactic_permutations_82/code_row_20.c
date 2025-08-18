#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

#define MAX_PAIRS 100

char* get_value_from_payload(const char *payload, const char *name) {
    static char value[256];
    size_t len = strlen(payload);
    char searchPattern[128];
    
    snprintf(searchPattern, sizeof(searchPattern), "%s=([^&]*)", name);

    const char *start = strstr(payload, searchPattern);
    if (start) {
        start += strlen(name) + 1; // Move past the `name=` part
        char *end = strchr(start, '&');
        if (!end) end = payload + len;
        
        size_t value_len = end - start;
        if (value_len < sizeof(value)) {
            strncpy(value, start, value_len);
            value[value_len] = '\0';
        }
    }

    return value[0] ? value : NULL;
}

void handle_request(const char *url) {
    const char *api_prefix = "/api?";
    
    if (strncmp(url, api_prefix, strlen(api_prefix)) == 0) {
        const char *payload = url + strlen(api_prefix);
        
        printf("Payload: %s\n", payload);

        char *name_value = get_value_from_payload(payload, "name");
        if (name_value) {
            printf("Name Value: %s\n", name_value);
        } else {
            printf("Parameter 'name' not found.\n");
        }
    } else {
        printf("Not an /api route.\n");
    }
}

int main() {
    const char *test_url = "/api?name=John&age=30";
    
    handle_request(test_url);
    
    return 0;
}