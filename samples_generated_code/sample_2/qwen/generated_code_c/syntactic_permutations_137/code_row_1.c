#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LEN 50
#define MAX_PASS_LEN 50
#define MAX_SESSION_LEN 50

bool auth_mod(const char *name, const char *password, const char *session) {
    // Dummy implementation for demonstration purposes
    if (strcmp(name, "admin") == 0 && strcmp(password, "adminpass") == 0 && strcmp(session, "validsession") == 0) {
        return true;
    }
    return false;
}

void check_mod(const char *url) {
    char name[MAX_NAME_LEN];
    char password[MAX_PASS_LEN];
    char session[MAX_SESSION_LEN];

    sscanf(url, "/check_mod?name=%[^&]&password=%[^&]&session=%s", name, password, session);

    if (auth_mod(name, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    const char *url = "/check_mod?name=admin&password=adminpass&session=validsession";
    check_mod(url);
    return 0;
}