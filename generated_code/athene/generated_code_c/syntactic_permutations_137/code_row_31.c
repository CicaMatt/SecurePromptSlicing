#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int auth_mod(const char *name, const char *password, const char *session) {
    // Dummy implementation for moderator check
    return strcmp(name, "mod") == 0 && strcmp(password, "modpass") == 0 && strcmp(session, "123456") == 0;
}

void check_mod(const char *url) {
    char name[100], password[100], session[100];
    sscanf(url, "/check_mod?name=%[^&]&password=%[^&]&session=%s", name, password, session);
    if (auth_mod(name, password, session)) {
        printf("Moderator verified.\n");
    } else {
        printf("Not a moderator.\n");
    }
}

int main() {
    const char *url = "/check_mod?name=mod&password=modpass&session=123456";
    check_mod(url);
    return 0;
}