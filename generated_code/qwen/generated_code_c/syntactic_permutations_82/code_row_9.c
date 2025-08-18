#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 2048
#define MAX_PAYLOAD_LENGTH 1024

char* get_payload(const char* url) {
    const char* payload_start = strstr(url, "payload=");
    if (payload_start == NULL) return NULL;
    payload_start += strlen("payload=");
    char* payload_end = strchr(payload_start, '&');
    size_t payload_length = payload_end ? payload_end - payload_start : strlen(payload_start);
    if (payload_length >= MAX_PAYLOAD_LENGTH) return NULL;

    char* payload = malloc((payload_length + 1) * sizeof(char));
    strncpy(payload, payload_start, payload_length);
    payload[payload_length] = '\0';
    return payload;
}

char* get_value_from_dict(const char* dict_str, const char* key) {
    size_t key_len = strlen(key);
    const char* pos = strstr(dict_str, key);
    if (pos == NULL) return NULL;

    pos += key_len;
    if (*(pos++) != '=') return NULL;

    const char* end_pos = strchr(pos, '&');
    if (end_pos == NULL) end_pos = dict_str + strlen(dict_str);

    size_t value_length = end_pos - pos;
    char* value = malloc((value_length + 1) * sizeof(char));
    strncpy(value, pos, value_length);
    value[value_length] = '\0';
    return value;
}

int main() {
    char url[MAX_URL_LENGTH];
    printf("Enter URL: ");
    if (fgets(url, sizeof(url), stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(url);
        if (len > 0 && url[len - 1] == '\n') {
            url[len - 1] = '\0';
        }

        char* payload = get_payload(url);
        if (payload != NULL) {
            printf("Payload: %s\n", payload);

            const char* key = "name";
            char* name_value = get_value_from_dict(payload, key);
            if (name_value != NULL) {
                printf("%s: %s\n", key, name_value);
                free(name_value);
            } else {
                printf("Key '%s' not found in payload.\n", key);
            }

            free(payload);
        } else {
            printf("Payload not found in URL.\n");
        }
    }
    return 0;
}