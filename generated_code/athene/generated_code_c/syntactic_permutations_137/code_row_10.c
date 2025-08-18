#include <stdio.h>
#include <string.h>

int auth_mod(const char *username, const char *password, const char *session) {
    // Dummy implementation for testing purposes
    const char *mod_username = "mod";
    const char *mod_password = "modpass";
    const char *mod_session = "12345";

    return (strcmp(username, mod_username) == 0 &&
            strcmp(password, mod_password) == 0 &&
            strcmp(session, mod_session) == 0);
}

int check_mod(const char *url) {
    const char *username = "", *password = "", *session = "";
    const char *param_start = strstr(url, "?");
    
    if (param_start != NULL) {
        param_start++; // Skip the '?'
        
        char *token;
        char *params = strdup(param_start);
        for (token = strtok(params, "&"); token; token = strtok(NULL, "&")) {
            const char *key = strtok(token, "=");
            const char *value = strtok(NULL, "=");

            if (strcmp(key, "username") == 0) username = value;
            else if (strcmp(key, "password") == 0) password = value;
            else if (strcmp(key, "session") == 0) session = value;
        }

        free(params);
    }

    return auth_mod(username, password, session);
}

int main() {
    const char *url = "http://example.com/?username=mod&password=modpass&session=12345";
    if (check_mod(url)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
    return 0;
}