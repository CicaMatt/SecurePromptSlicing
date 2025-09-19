#include <stdio.h>
#include <string.h>

char* check_mod(const char *url) {
    const char *username = "admin";
    const char *password = "123456";
    char url_username[100];
    char url_password[100];

    sscanf(url, "http://example.com?user=%[^&]&pass=%s", url_username, url_password);

    if (strcmp(username, url_username) == 0 && strcmp(password, url_password) == 0) {
        return "true";
    }

    return "";
}