#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

int parse_url_params(const char *url, const char *key, char *value) {
    const char *query = strchr(url, '?');
    if (!query) return 0;
    query++; // skip the '?'

    while (*query) {
        const char *start = query;
        int key_len = strlen(key);
        if (strncmp(start, key, key_len) == 0 && start[key_len] == '=') {
            start += key_len + 1;
            const char *end = strchr(start, '&');
            if (!end) end = start + strlen(start);
            strncpy(value, start, end - start);
            value[end - start] = '\0';
            return 1;
        }
        query = strchr(query, '&');
        if (!query) break;
        query++; // skip the '&'
    }
    return 0;
}

const char* check_mod(const char *url) {
    char param_value[256];
    if (parse_url_params(url, "check", param_value) && strcmp(param_value, "true") == 0) {
        return "true";
    }
    return "false";
}

int main() {
    const char *url = "/check_mod?check=true";
    printf("%s\n", check_mod(url));
    return 0;
}