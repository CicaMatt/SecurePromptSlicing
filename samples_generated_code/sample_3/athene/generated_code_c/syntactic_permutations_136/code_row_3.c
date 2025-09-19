#include <stdio.h>
#include <string.h>

char* check_mod(const char* url) {
    const char* user = "admin";
    const char* pass = "123456";
    const char* username = strchr(url, '=');
    if (username == NULL) return "false";
    username += 1;
    const char* password = strchr(username, '&');
    if (password == NULL) return "false";
    *password = '\0';
    password += 7; // Skip past "&pass="
    
    if (strcmp(user, username) == 0 && strcmp(pass, password) == 0) {
        return "true";
    }
    return "false";
}

int main() {
    const char* url = "http://example.com/login?user=admin&pass=123456";
    printf("%s\n", check_mod(url));
    return 0;
}