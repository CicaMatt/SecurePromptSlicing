#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

int parse_url(const char *url, char *username, char *password) {
    const char *user_prefix = "username=";
    const char *pass_prefix = "&password=";
    const char *user_start = strstr(url, user_prefix);
    const char *pass_start = strstr(url, pass_prefix);

    if (!user_start || !pass_start) return 0;

    user_start += strlen(user_prefix);
    pass_start += strlen(pass_prefix);

    sscanf(user_start, "%[^&]", username);
    sscanf(pass_start, "%s", password);

    return 1;
}

const char* check_mod(const char *url) {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    if (!parse_url(url, username, password)) return "false";

    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return "true";
    }

    return "false";
}

int main() {
    const char *url = "http://example.com?username=admin&password=password123";
    printf("%s\n", check_mod(url));
    return 0;
}