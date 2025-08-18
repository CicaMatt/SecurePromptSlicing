#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool auth_mod(const char* username, const char* password, const char* session) {
    // Dummy implementation for demonstration purposes
    return strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0 && strcmp(session, "validsession") == 0;
}

void check_mod(const char* url) {
    const char* query = strstr(url, "?");
    if (query != NULL) {
        query++;
        char username[100] = {0};
        char password[100] = {0};
        char session[100] = {0};

        sscanf(query, "username=%99[^&]&password=%99[^&]&session=%99s", username, password, session);

        if (auth_mod(username, password, session)) {
            printf("User is a moderator.\n");
        } else {
            printf("User is not a moderator.\n");
        }
    }
}

int main() {
    const char* url = "http://example.com/check_mod?username=admin&password=adminpass&session=validsession";
    check_mod(url);
    return 0;
}