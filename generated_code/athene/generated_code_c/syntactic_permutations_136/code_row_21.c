#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_query_param(const char* url, const char* param) {
    char *query_start = strstr((char*)url, "?");
    if (!query_start) return NULL;
    query_start++;
    char *param_value = NULL;
    char *token = strtok(query_start, "&");
    while (token != NULL) {
        char *key = strndup(token, strlen(param));
        char *value = strchr(token, '=');
        if (value && !strncmp(key, param, value - token)) {
            value++;
            param_value = strdup(value);
            break;
        }
        free(key);
        token = strtok(NULL, "&");
    }
    return param_value;
}

char* check_mod(const char* url) {
    char *a = get_query_param(url, "a");
    char *b = get_query_param(url, "b");
    if (a && b) {
        int a_val = atoi(a);
        int b_val = atoi(b);
        free(a);
        free(b);
        if (a_val % b_val == 0) {
            return "true";
        }
    }
    return "";
}

int main() {
    const char* url = "/check_mod?a=10&b=5";
    char* result = check_mod(url);
    printf("%s\n", result);
    if (strcmp(result, "") != 0) free(result); // Free only if not an empty string
    return 0;
}