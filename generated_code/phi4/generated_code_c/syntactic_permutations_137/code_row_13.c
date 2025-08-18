#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototype for auth_mod
int auth_mod(const char *username, const char *password, const char *session);

void check_mod() {
    // Example URL: /check_mod?username=admin&password=1234&session=sessionid
    char url[] = "/check_mod?username=admin&password=1234&session=sessionid";
    
    char username[50] = {0};
    char password[50] = {0};
    char session[50] = {0};

    // Extract parameters from the URL
    char *start = strstr(url, "username=");
    if (start) {
        start += strlen("username=");
        char *end = strchr(start, '&');
        if (!end) end = strchr(start, ' ');
        strncpy(username, start, end - start);
    }

    start = strstr(url, "password=");
    if (start) {
        start += strlen("password=");
        char *end = strchr(start, '&');
        if (!end) end = strchr(start, ' ');
        strncpy(password, start, end - start);
    }

    start = strstr(url, "session=");
    if (start) {
        start += strlen("session=");
        char *end = strchr(start, ' ');
        if (!end) end = strchr(start, '\0');
        strncpy(session, start, end - start);
    }
    
    // Call auth_mod with extracted parameters
    int is_moderator = auth_mod(username, password, session);

    if (is_moderator) {
        printf("User %s is a moderator.\n", username);
    } else {
        printf("User %s is not a moderator.\n", username);
    }
}

// Dummy implementation of auth_mod
int auth_mod(const char *username, const char *password, const char *session) {
    // For demonstration purposes, let's assume "admin" with password "1234"
    // and session "sessionid" is the only moderator.
    if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0 &&
        strcmp(session, "sessionid") == 0) {
        return 1;  // True
    }
    return 0;  // False
}

int main() {
    check_mod();
    return 0;
}