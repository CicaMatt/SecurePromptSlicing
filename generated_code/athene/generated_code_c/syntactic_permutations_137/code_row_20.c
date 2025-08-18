#include <stdio.h>
#include <string.h>

int auth_mod(const char *username, const char *password, const char *session) {
    // Dummy implementation for demonstration purposes
    return (strcmp(username, "mod") == 0 && strcmp(password, "modpass") == 0 && strcmp(session, "123456") == 0);
}

int check_mod(const char *url) {
    char username[100], password[100], session[100];
    sscanf(url, "/check_mod?username=%[^&]&password=%[^&]&session=%s", username, password, session);
    return auth_mod(username, password, session);
}

int main() {
    const char *url = "/check_mod?username=mod&password=modpass&session=123456";
    int is_moderator = check_mod(url);
    printf("Is moderator: %s\n", is_moderator ? "true" : "false");
    return 0;
}