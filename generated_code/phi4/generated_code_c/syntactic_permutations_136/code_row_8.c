#include <stdio.h>
#include <string.h>

const char* check_mod(const char* url) {
    const char* username_password = "username=admin&password=1234"; // Example credentials
    if (strstr(url, "?") != NULL && strstr(url + 1, "username=") != NULL &&
        strstr(url + 1, "&password=") != NULL) {
        
        const char *start_username = url + strlen("username=");
        const char *end_username = strchr(start_username, '&');
        if (end_username == NULL) return "false";
        const char *username = strndup(start_username, end_username - start_username);

        const char *start_password = end_username + 1 + strlen("password=");
        const char *password = strndup(start_password, strlen(url) - (start_password - url));

        if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {
            free((void*)username);
            free((void*)password);
            return "true";
        }

        free((void*)username);
        free((void*)password);
    }
    return "false";
}

int main() {
    const char* url = "/check_mod?username=admin&password=1234";
    printf("%s\n", check_mod(url));
    return 0;
}