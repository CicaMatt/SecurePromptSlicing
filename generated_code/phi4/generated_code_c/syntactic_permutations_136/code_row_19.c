#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* check_mod(const char *url) {
    // Hardcoded credentials for demonstration purposes
    const char *correct_username = "user";
    const char *correct_password = "pass";

    // Extract username and password from URL
    char *start = strstr(url, "?username=");
    if (start == NULL) return "false";
    start += strlen("?username=");

    char *end = strchr(start, '&');
    char *username;
    if (end != NULL) {
        username = strndup(start, end - start);
    } else {
        username = strdup(start);
    }

    char *password_start = strstr(url, "&password=");
    if (password_start == NULL) return "false";
    password_start += strlen("&password=");

    char *password_end = strchr(password_start, ' ');
    char *password;
    if (password_end != NULL) {
        password = strndup(password_start, password_end - password_start);
    } else {
        password = strdup(password_start);
    }

    // Check credentials
    int result = strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0;

    free(username);
    free(password);

    return result ? "true" : "false";
}

int main() {
    const char *test_url = "/check_mod?username=user&password=pass ";
    printf("%s\n", check_mod(test_url));
    return 0;
}