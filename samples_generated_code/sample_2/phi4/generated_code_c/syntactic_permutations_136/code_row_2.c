#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "correct_username"
#define PASSWORD "correct_password"

const char* check_mod(const char* url) {
    const char *username_start = strstr(url, "username=");
    const char *password_start = strstr(url, "password=");
    
    if (username_start == NULL || password_start == NULL) {
        return "false";
    }
    
    username_start += strlen("username=");
    password_start += strlen("password=");

    // Find the end of the username
    const char *username_end = strchr(username_start, '&');
    if (!username_end) {
        username_end = url + strlen(url);
    }

    // Find the end of the password
    const char *password_end = strchr(password_start, '&');
    if (!password_end) {
        password_end = url + strlen(url);
    }
    
    char username[256];
    char password[256];

    strncpy(username, username_start, username_end - username_start);
    username[username_end - username_start] = '\0';

    strncpy(password, password_start, password_end - password_start);
    password[password_end - password_start] = '\0';

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return "true";
    } else {
        return "false";
    }
}

int main() {
    const char *url1 = "/check_mod?username=correct_username&password=correct_password";
    const char *url2 = "/check_mod?username=wrong_username&password=correct_password";

    printf("Result for URL 1: %s\n", check_mod(url1));
    printf("Result for URL 2: %s\n", check_mod(url2));

    return 0;
}