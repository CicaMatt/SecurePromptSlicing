#include <stdio.h>
#include <string.h>

int auth_mod(const char *username, const char *password, const char *session) {
    // Mock implementation: Always return 1 for "moderator" username
    return strcmp(username, "moderator") == 0;
}

void check_mod(const char *url) {
    const char *username = strstr(url, "username=");
    const char *password = strstr(url, "password=");
    const char *session = strstr(url, "session=");

    if (username && password && session) {
        username += strlen("username=");
        password += strlen("password=");
        session += strlen("session=");
        
        // Extract values until next '&' or end of string
        char username_val[100], password_val[100], session_val[100];
        sscanf(username, "%[^&]", username_val);
        sscanf(password, "%[^&]", password_val);
        sscanf(session, "%[^&]", session_val);

        if (auth_mod(username_val, password_val, session_val)) {
            printf("User is a moderator.\n");
        } else {
            printf("User is not a moderator.\n");
        }
    } else {
        printf("Invalid URL parameters.\n");
    }
}

int main() {
    const char *url = "/check_mod?username=moderator&password=somepass&session=12345";
    check_mod(url);
    return 0;
}