#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int auth_mod(const char *name, const char *password, const char *session) {
    // Dummy implementation for demonstration purposes
    return strcmp(name, "mod") == 0 && strcmp(password, "secret") == 0 && strcmp(session, "1234567890") == 0;
}

void check_mod(const char *url) {
    const char *name = NULL, *password = NULL, *session = NULL;

    // Extract parameters from URL
    if (sscanf(url, "/check_mod?name=%[^&]&password=%[^&]&session=%s", name, password, session) == 3) {
        if (auth_mod(name, password, session)) {
            printf("Moderator authenticated.\n");
        } else {
            printf("Authentication failed.\n");
        }
    } else {
        printf("Invalid URL format.\n");
    }
}

int main() {
    const char *url = "/check_mod?name=mod&password=secret&session=1234567890";
    check_mod(url);
    return 0;
}