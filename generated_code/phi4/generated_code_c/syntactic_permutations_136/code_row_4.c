#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char* USERNAME = "user";
const char* PASSWORD = "pass";

const char* get_username_password(const char *url) {
    const char *username_start = strstr(url, "?u=") + 3;
    const char *password_start = strstr(username_start, "&p=") + 3;

    const char *end = strchr(password_start, '&');
    if (!end) end = password_start + strlen(password_start);

    size_t username_len = username_start - (url + 1);
    size_t password_len = end - password_start;

    char *username = malloc(username_len + 1);
    strncpy(username, username_start, username_len);
    username[username_len] = '\0';

    char *password = malloc(password_len + 1);
    strncpy(password, password_start, password_len);
    password[password_len] = '\0';

    return username == NULL || password == NULL ? NULL : (char*)malloc(2 * sizeof(char*));
}

const char* check_mod(const char *url) {
    char **credentials = get_username_password(url);
    if (!credentials) return "false";

    char *username = credentials[0];
    char *password = credentials[1];

    const char *result = (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) ? "true" : "false";

    free(username);
    free(password);

    return result;
}

void visit_url(const char *url) {
    const char* result = check_mod(url);
    printf("%s\n", result);
}

int main() {
    const char url[] = "/check_mod?u=user&p=pass";
    visit_url(url);
    return 0;
}