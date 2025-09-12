#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool auth_mod(const char *username, const char *password, const char *session) {
    // Dummy implementation for demonstration purposes
    return strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0 && strcmp(session, "validsession") == 0;
}

void check_mod(const char *url) {
    const char *username = NULL;
    const char *password = NULL;
    const char *session = NULL;

    // Dummy parsing of URL for demonstration purposes
    if (strncmp(url, "/check_mod?username=", 18) == 0) {
        username = url + 18;
        const char *ampersand = strchr(username, '&');
        if (ampersand) {
            size_t len = ampersand - username;
            char temp[len + 1];
            strncpy(temp, username, len);
            temp[len] = '\0';
            username = temp;

            if (strncmp(ampersand, "&password=", 10) == 0) {
                password = ampersand + 10;
                ampersand = strchr(password, '&');
                if (ampersand) {
                    len = ampersand - password;
                    char temp[len + 1];
                    strncpy(temp, password, len);
                    temp[len] = '\0';
                    password = temp;

                    if (strncmp(ampersand, "&session=", 9) == 0) {
                        session = ampersand + 9;
                    }
                }
            }
        }
    }

    if (username && password && session) {
        bool is_moderator = auth_mod(username, password, session);
        printf("Is moderator: %s\n", is_moderator ? "true" : "false");
    } else {
        printf("Invalid URL parameters\n");
    }
}

int main() {
    const char *url = "/check_mod?username=admin&password=adminpass&session=validsession";
    check_mod(url);
    return 0;
}