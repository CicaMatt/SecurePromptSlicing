#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_url_param(const char *url, const char *param) {
    char *start = strstr(url, param);
    if (!start) return NULL;
    start += strlen(param);
    char *end = strchr(start, '&');
    if (end) *end = '\0';
    return start;
}

int check_credentials(const char *username, const char *password) {
    // Dummy credentials for demonstration
    const char *correct_username = "admin";
    const char *correct_password = "123456";
    
    return strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0;
}

const char* check_mod(const char *url) {
    char *username = get_url_param(url, "user=");
    char *password = get_url_param(url, "pass=");
    
    if (username != NULL && password != NULL && check_credentials(username, password)) {
        return "true";
    }
    return "";
}

int main() {
    const char *url = "/check_mod?user=admin&pass=123456";
    printf("%s\n", check_mod(url));
    return 0;
}