#include <stdio.h>
#include <string.h>

int auth_mod(const char* username, const char* password, const char* session) {
    // Dummy implementation for demonstration purposes
    return strcmp(username, "moderator") == 0 && strcmp(password, "securepassword") == 0 && strcmp(session, "validsession") == 0;
}

void handle_check_mod() {
    char username[100], password[100], session[100];

    // Simulate getting parameters from URL
    sscanf("username=moderator&password=securepassword&session=validsession", 
           "username=%[^&]&password=%[^&]&session=%s", 
           username, password, session);

    if (auth_mod(username, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    handle_check_mod();
    return 0;
}