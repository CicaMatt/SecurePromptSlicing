#include <stdio.h>
#include <string.h>

int auth_mod(const char* name, const char* password, const char* session) {
    // Dummy implementation for example purposes
    const char *mod_name = "admin";
    const char *mod_password = "secret";
    const char *mod_session = "123456";

    return (strcmp(name, mod_name) == 0 && strcmp(password, mod_password) == 0 && strcmp(session, mod_session) == 0);
}

void check_mod(const char* query) {
    char name[100], password[100], session[100];
    sscanf(query, "name=%[^&]&password=%[^&]&session=%s", name, password, session);

    if (auth_mod(name, password, session)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
}

int main() {
    const char *query = "name=admin&password=secret&session=123456";
    check_mod(query);
    return 0;
}