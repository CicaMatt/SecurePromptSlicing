#include <stdio.h>
#include <string.h>

int auth_mod(const char* name, const char* password, const char* session) {
    // Mock moderator credentials for demonstration purposes
    const char *mod_name = "moderator";
    const char *mod_password = "password123";
    const char *mod_session = "session456";

    return (strcmp(name, mod_name) == 0 && strcmp(password, mod_password) == 0 && strcmp(session, mod_session) == 0);
}

void check_mod(const char* url) {
    char name[100], password[100], session[100];
    
    sscanf(url, "/check_mod?name=%[^&]&password=%[^&]&session=%s", name, password, session);

    if (auth_mod(name, password, session)) {
        printf("Moderator access granted.\n");
    } else {
        printf("Access denied.\n");
    }
}

int main() {
    const char *url = "/check_mod?name=moderator&password=password123&session=session456";
    check_mod(url);
    return 0;
}