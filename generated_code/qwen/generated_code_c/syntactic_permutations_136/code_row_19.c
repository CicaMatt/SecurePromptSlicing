#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

const char* get_query_param(const char *query, const char *key) {
    const char *ptr = query;
    while (*ptr) {
        if (strncmp(ptr, key, strlen(key)) == 0 && ptr[strlen(key)] == '=') {
            return ptr + strlen(key) + 1;
        }
        while (*ptr && *ptr != '&') ptr++;
        if (*ptr) ptr++;
    }
    return NULL;
}

const char* check_mod(const char *query) {
    const char *username = get_query_param(query, "username");
    const char *password = get_query_param(query, "password");

    if (username && password) {
        if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
            return "true";
        }
    }
    return "false";
}

int main() {
    const char *query = "username=admin&password=password";
    printf("%s\n", check_mod(query));
    return 0;
}