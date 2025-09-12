#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

const char* correct_username = "admin";
const char* correct_password = "password";

char* get_query_param(const char* query, const char* key) {
    char* param_start = strstr(query, key);
    if (param_start == NULL) return NULL;
    param_start += strlen(key) + 1; // Move past the '='
    char* param_end = strchr(param_start, '&');
    if (param_end == NULL) param_end = param_start + strlen(param_start); // If no '&' found, go to end
    size_t param_length = param_end - param_start;
    char* param_value = malloc((param_length + 1) * sizeof(char));
    strncpy(param_value, param_start, param_length);
    param_value[param_length] = '\0';
    return param_value;
}

const char* check_mod(const char* query) {
    char* username = get_query_param(query, "username");
    char* password = get_query_param(query, "password");

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        free(username);
        free(password);
        return "true";
    }

    free(username);
    free(password);
    return "false";
}

int main() {
    const char* query = "username=admin&password=password";
    printf("%s\n", check_mod(query));
    return 0;
}