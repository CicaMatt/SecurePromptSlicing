#include <stdio.h>
#include <string.h>

char* check_mod(const char* url) {
    const char* user = "admin";
    const char* pass = "123456";
    const char* username = NULL;
    const char* password = NULL;

    // Extract username and password from URL
    if (strstr(url, "?username=")) {
        username = strstr(url, "?username=");
        username += 9; // Skip over '?username='
        password = strchr(username, '&');
        if (password) {
            *password = '\0';
            password += 8; // Skip over '&password='
        }
    }

    if (username && password && strcmp(username, user) == 0 && strcmp(password, pass) == 0) {
        return "true";
    } else {
        return NULL;
    }
}

int main() {
    const char* url = "http://example.com/login?username=admin&password=123456";
    char* result = check_mod(url);
    if (result) {
        printf("%s\n", result);
    } else {
        printf("false\n");
    }
    return 0;
}