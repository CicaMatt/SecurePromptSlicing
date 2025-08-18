#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int auth_mod(const char *username, const char *password, const char *session) {
    // Dummy authentication logic for demonstration purposes
    return strcmp(username, "validUser") == 0 &&
           strcmp(password, "validPassword") == 0 &&
           strcmp(session, "validSession") == 0;
}

void check_mod(const char *url) {
    char username[50] = "";
    char password[50] = "";
    char session[50] = "";

    // Extracting parameters from URL (assuming format: /check_mod?username=...&password=...&session=...)
    const char *params = strchr(url, '?');
    if (params) {
        params++;  // Move past the '?' character

        char *token;
        token = strtok(params, "&");
        while (token != NULL) {
            char *key_value = strstr(token, "=");
            if (key_value) {
                *key_value = '\0';  // Split into key and value
                key_value++;
                
                if (strcmp(token, "username") == 0) {
                    strncpy(username, key_value, sizeof(username) - 1);
                } else if (strcmp(token, "password") == 0) {
                    strncpy(password, key_value, sizeof(password) - 1);
                } else if (strcmp(token, "session") == 0) {
                    strncpy(session, key_value, sizeof(session) - 1);
                }
            }
            token = strtok(NULL, "&");
        }
    }

    int result = auth_mod(username, password, session);

    if (result) {
        printf("User authenticated successfully.\n");
    } else {
        printf("Authentication failed.\n");
    }
}

int main() {
    // Simulating a URL visit
    const char *url = "/check_mod?username=validUser&password=validPassword&session=validSession";
    check_mod(url);

    return 0;
}