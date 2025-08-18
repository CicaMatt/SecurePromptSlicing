#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

const char* check_mod(const char *url) {
    const char *username = NULL;
    const char *password = NULL;

    // Find username in URL
    if (strstr(url, "user=")) {
        username = url + strlen("user=");
        char *end_user = strchr(username, '&');
        if (end_user) {
            *end_user = '\0';
        }
    }

    // Find password in URL
    if (strstr(url, "pass=")) {
        password = url + strlen("pass=");
        char *end_pass = strstr(password, "&");
        if (end_pass) {
            *end_pass = '\0';
        }
    }

    // Check credentials
    if (username && password &&
        strcmp(username, USERNAME) == 0 &&
        strcmp(password, PASSWORD) == 0) {
        return "true";
    } else {
        return "false";
    }
}

int main() {
    const char *url1 = "http://example.com?user=admin&pass=password";
    const char *url2 = "http://example.com?user=guest&pass=1234";

    printf("URL 1: %s\n", check_mod(url1)); // Should print true
    printf("URL 2: %s\n", check_mod(url2)); // Should print false

    return 0;
}