#include <stdio.h>
#include <string.h>

int auth_mod(const char *username, const char *password, const char *session) {
    // Dummy implementation for demonstration purposes
    const char *mod_username = "admin";
    const char *mod_password = "123456";
    const char *mod_session = "abc123";

    return (strcmp(username, mod_username) == 0 &&
            strcmp(password, mod_password) == 0 &&
            strcmp(session, mod_session) == 0);
}

void check_mod() {
    char username[100], password[100], session[100];
    
    // Simulate getting input from URL parameters (for demonstration purposes)
    strcpy(username, "admin");
    strcpy(password, "123456");
    strcpy(session, "abc123");

    if (auth_mod(username, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    check_mod();
    return 0;
}