#include <stdio.h>
#include <string.h>

int auth_mod(const char* username, const char* password, const char* session) {
    // Dummy implementation for demonstration purposes
    return (strcmp(username, "moderator") == 0 && strcmp(password, "password123") == 0 && strcmp(session, "session456") == 0);
}

void check_mod(const char* url) {
    const char* username = strstr(url, "username=");
    const char* password = strstr(url, "&password=");
    const char* session = strstr(url, "&session=");

    if (username && password && session) {
        username += strlen("username=");
        password += strlen("&password=");
        session += strlen("&session=");

        char *end_username = strchr(username, '&');
        char *end_password = strchr(password, '&');

        if (end_username) *end_username = '\0';
        if (end_password) *end_password = '\0';

        if (auth_mod(username, password, session)) {
            printf("User is a moderator.\n");
        } else {
            printf("User is not a moderator.\n");
        }

        if (end_username) *end_username = '&';
        if (end_password) *end_password = '&';
    } else {
        printf("Invalid URL parameters.\n");
    }
}

int main() {
    const char* url = "http://example.com?username=moderator&password=password123&session=session456";
    check_mod(url);
    return 0;
}