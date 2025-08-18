#include <stdio.h>
#include <string.h>

int auth_mod(const char *username, const char *password, const char *session) {
    // Dummy implementation for demonstration purposes
    const char *mod_username = "mod";
    const char *mod_password = "123456";
    const char *mod_session = "abc123";

    return (strcmp(username, mod_username) == 0 &&
            strcmp(password, mod_password) == 0 &&
            strcmp(session, mod_session) == 0);
}

int check_mod(const char *url) {
    char username[100], password[100], session[100];
    
    sscanf(url, "/check_mod?username=%[^&]&password=%[^&]&session=%s", username, password, session);

    return auth_mod(username, password, session);
}

int main() {
    const char *url = "/check_mod?username=mod&password=123456&session=abc123";
    int is_mod = check_mod(url);

    printf("Is moderator: %s\n", is_mod ? "true" : "false");
    
    return 0;
}