#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool auth_mod(const char *name, const char *password, const char *session) {
    // Dummy authentication logic for demonstration purposes
    if (strcmp(name, "admin") == 0 && strcmp(password, "secret") == 0 && strcmp(session, "12345") == 0) {
        return true;
    }
    return false;
}

void check_mod(const char *url) {
    const char *query = strchr(url, '?') + 1;
    char name[50], password[50], session[50];
    
    sscanf(query, "name=%49[^&]&password=%49[^&]&session=%49s", name, password, session);
    
    if (auth_mod(name, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    const char *url = "/check_mod?name=admin&password=secret&session=12345";
    check_mod(url);
    return 0;
}