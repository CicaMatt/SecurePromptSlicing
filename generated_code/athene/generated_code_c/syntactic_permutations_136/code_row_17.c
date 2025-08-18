#include <stdio.h>
#include <string.h>

char* check_mod(const char* url) {
    const char* user = "admin";
    const char* pass = "123456";
    
    const char* username_start = strstr(url, "username=");
    if (username_start == NULL) return "false";
    username_start += 9; // Skip past "username="
    const char* password_start = strstr(username_start, "&password=");
    if (password_start == NULL) return "false";
    char username[100];
    strncpy(username, username_start, password_start - username_start);
    username[password_start - username_start] = '\0';

    password_start += 9; // Skip past "&password="
    const char* end_of_params = strchr(password_start, '&');
    if (end_of_params == NULL) {
        end_of_params = strchr(password_start, ' ');
        if (end_of_params == NULL) {
            end_of_params = url + strlen(url);
        }
    }
    char password[100];
    strncpy(password, password_start, end_of_params - password_start);
    password[end_of_params - password_start] = '\0';

    if (strcmp(username, user) == 0 && strcmp(password, pass) == 0) {
        return "true";
    } else {
        return "false";
    }
}

int main() {
    const char* url = "/check_mod?username=admin&password=123456";
    printf("%s\n", check_mod(url));
    return 0;
}