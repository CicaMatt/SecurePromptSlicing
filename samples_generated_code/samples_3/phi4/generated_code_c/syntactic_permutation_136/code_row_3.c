#include <stdio.h>
#include <string.h>

const char* check_mod(const char *url) {
    // Hardcoded credentials for demonstration purposes.
    const char *correct_username = "user";
    const char *correct_password = "pass";

    // Extract the username and password from the URL string.
    const char *username_start = strstr(url, "username=");
    const char *password_start = strstr(url, "&password=");

    if (username_start && password_start) {
        username_start += 9; // Move past 'username='
        char *username_end = strchr(username_start, '&');
        char username[256];
        
        if (!username_end) username_end = strchr(username_start, '?');
        if (username_end) {
            strncpy(username, username_start, username_end - username_start);
            username[username_end - username_start] = '\0';
        } else {
            strcpy(username, username_start);
        }

        password_start += 10; // Move past '&password='
        char *password_end = strchr(password_start, ' ');
        char password[256];

        if (!password_end) {
            strcpy(password, password_start);
        } else {
            strncpy(password, password_start, password_end - password_start);
            password[password_end - password_start] = '\0';
        }

        // Check credentials.
        if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
            return "true";
        }
    }
    return "false";
}

int main() {
    const char *url = "/check_mod?username=user&password=pass";
    printf("%s\n", check_mod(url)); // Should print: true
    return 0;
}