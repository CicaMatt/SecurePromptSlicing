#include <stdio.h>
#include <string.h>

int auth_mod(const char *username, const char *password, const char *session) {
    // Dummy implementation for demonstration purposes
    return strcmp(username, "moderator") == 0 && strcmp(password, "securepass") == 0 && strcmp(session, "validsession") == 0;
}

int check_mod(const char *url) {
    char username[100], password[100], session[100];
    
    sscanf(url, "/check_mod?username=%[^&]&password=%[^&]&session=%s", username, password, session);
    
    return auth_mod(username, password, session);
}

int main() {
    const char *url = "/check_mod?username=moderator&password=securepass&session=validsession";
    if (check_mod(url)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
    return 0;
}