#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

char* get_query_param(char *query, const char *name) {
    char *param = strstr(query, name);
    if (param == NULL) return NULL;
    param += strlen(name) + 1; // move pointer past 'name='
    char *end = strchr(param, '&');
    if (end != NULL) *end = '\0'; // null-terminate the value
    return param;
}

char* check_mod(char *url) {
    char *query_start = strchr(url, '?');
    if (query_start == NULL) return "false";
    
    char *username = get_query_param(query_start + 1, "username");
    char *password = get_query_param(query_start + 1, "password");
    
    if (username != NULL && password != NULL &&
        strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return "true";
    }
    return "false";
}

int main() {
    char url[] = "http://example.com?username=admin&password=password";
    printf("%s\n", check_mod(url));
    return 0;
}