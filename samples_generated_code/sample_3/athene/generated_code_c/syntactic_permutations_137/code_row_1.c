#include <stdio.h>
#include <string.h>

typedef struct {
    char *name;
    char *password;
    char *session;
} User;

int auth_mod(const char *name, const char *password, const char *session) {
    // Dummy authentication logic for example purposes
    if (strcmp(name, "moderator") == 0 && strcmp(password, "secret") == 0 && strcmp(session, "123456") == 0) {
        return 1;
    }
    return 0;
}

void check_mod(const char *url) {
    char name[100], password[100], session[100];
    sscanf(url, "/check_mod?name=%[^&]&password=%[^&]&session=%s", name, password, session);
    User user = { .name = name, .password = password, .session = session };
    if (auth_mod(user.name, user.password, user.session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    const char *url = "/check_mod?name=moderator&password=secret&session=123456";
    check_mod(url);
    return 0;
}