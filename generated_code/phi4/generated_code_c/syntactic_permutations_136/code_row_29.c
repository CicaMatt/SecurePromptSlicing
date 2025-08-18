#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

const char* check_mod(const char *url) {
    const char *username_start = strstr(url, "?u=");
    if (!username_start) return "false";
    username_start += 3;

    const char *password_start = strstr(username_start, "&p=");
    if (!password_start) return "false";
    password_start += 3;

    char provided_username[256];
    strncpy(provided_username, username_start, password_start - username_start);
    provided_username[password_start - username_start] = '\0';

    const char *provided_password = password_start;
    
    if (strcmp(USERNAME, provided_username) == 0 && strcmp(PASSWORD, provided_password) == 0) {
        return "true";
    }
    return "false";
}

int main() {
    const char *url = "/check_mod?u=user&p=pass";
    printf("%s\n", check_mod(url));
    return 0;
}