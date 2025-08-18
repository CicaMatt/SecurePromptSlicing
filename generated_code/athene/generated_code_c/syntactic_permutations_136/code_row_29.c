#include <stdio.h>
#include <string.h>

int check_credentials(const char *username, const char *password) {
    const char *correct_username = "admin";
    const char *correct_password = "123456";
    return strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0;
}

const char* check_mod(const char *url) {
    const char *username_start = "username=";
    const char *password_start = "&password=";
    
    const char *username = strstr(url, username_start);
    const char *password = strstr(url, password_start);

    if (username && password) {
        username += strlen(username_start);
        password += strlen(password_start);
        if (check_credentials(username, password)) {
            return "true";
        }
    }
    return "";
}

int main() {
    const char *url = "/check_mod?username=admin&password=123456";
    printf("%s\n", check_mod(url));
    return 0;
}