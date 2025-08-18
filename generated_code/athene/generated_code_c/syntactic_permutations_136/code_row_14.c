#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_query_param(const char *url, const char *param) {
    char *query_start = strchr((char*)url, '?');
    if (!query_start) return NULL;
    query_start++;
    char *key_value_pairs = strdup(query_start);
    char *token = strtok(key_value_pairs, "&");
    while (token != NULL) {
        char *value;
        if (sscanf(token, "%*[^=]=%ms", &value) == 1) {
            if (strncmp(token, param, strlen(param)) == 0) {
                return value;
            }
            free(value);
        }
        token = strtok(NULL, "&");
    }
    free(key_value_pairs);
    return NULL;
}

char* check_mod(const char *url) {
    const char *username = get_query_param(url, "user");
    const char *password = get_query_param(url, "pass");

    if (username && password && strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0) {
        return "true";
    }
    return "";
}

int main() {
    const char *url = "/check_mod?user=admin&pass=123456";
    char *result = check_mod(url);
    printf("%s\n", result);
    free(result); // Free the allocated memory if get_query_param was successful
    return 0;
}