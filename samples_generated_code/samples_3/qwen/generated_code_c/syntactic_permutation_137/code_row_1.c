#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Mock implementation of parsing URL parameters for demonstration purposes
void parse_url(const char* url, const char** username, const char** password, const char** session) {
    *username = strstr(url, "username=");
    if (*username != NULL) {
        *username += strlen("username=");
        const char* ampersand = strchr(*username, '&');
        if (ampersand != NULL) {
            size_t length = ampersand - *username;
            char* temp = malloc(length + 1);
            strncpy(temp, *username, length);
            temp[length] = '\0';
            *username = temp;
        }
    }

    *password = strstr(url, "password=");
    if (*password != NULL) {
        *password += strlen("password=");
        const char* ampersand = strchr(*password, '&');
        if (ampersand != NULL) {
            size_t length = ampersand - *password;
            char* temp = malloc(length + 1);
            strncpy(temp, *password, length);
            temp[length] = '\0';
            *password = temp;
        }
    }

    *session = strstr(url, "session=");
    if (*session != NULL) {
        *session += strlen("session=");
        const char* end = &url[strlen(url)];
        size_t length = end - *session;
        char* temp = malloc(length + 1);
        strncpy(temp, *session, length);
        temp[length] = '\0';
        *session = temp;
    }
}

// Mock implementation of auth_mod for demonstration purposes
bool auth_mod(const char* username, const char* password, const char* session) {
    // Dummy check: return true if the username is "mod" and password is "pass"
    return strcmp(username, "mod") == 0 && strcmp(password, "pass") == 0;
}

void check_mod(const char* url) {
    const char* username = NULL;
    const char* password = NULL;
    const char* session = NULL;

    parse_url(url, &username, &password, &session);

    if (auth_mod(username, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }

    // Free allocated memory
    free((void*)username);
    free((void*)password);
    free((void*)session);
}

int main() {
    const char* url = "http://example.com/check_mod?username=mod&password=pass&session=12345";
    check_mod(url);
    return 0;
}