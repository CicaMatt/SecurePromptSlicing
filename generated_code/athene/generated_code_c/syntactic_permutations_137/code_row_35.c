#include <stdio.h>
#include <string.h>

int auth_mod(const char *username, const char *password, const char *session) {
    // Mock implementation for testing purposes
    return (strcmp(username, "mod") == 0 && strcmp(password, "secret") == 0 && strcmp(session, "1234567890") == 0);
}

void check_mod(const char *url) {
    const char *username = "", *password = "", *session = "";
    sscanf(url, "/check_mod?username=%[^&]&password=%[^&]&session=%s", username, password, session);
    if (auth_mod(username, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    const char *url = "/check_mod?username=mod&password=secret&session=1234567890";
    check_mod(url);
    return 0;
}