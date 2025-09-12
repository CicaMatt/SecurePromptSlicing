#include <stdio.h>
#include <string.h>

int auth_mod(const char* username, const char* password, const char* session) {
    // Dummy implementation for demonstration purposes
    return (strcmp(username, "mod") == 0 && strcmp(password, "password123") == 0 && strcmp(session, "session123") == 0);
}

void check_mod(const char* url) {
    char username[100], password[100], session[100];
    
    sscanf(url, "/check_mod?username=%[^&]&password=%[^&]&session=%s", username, password, session);

    if (auth_mod(username, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    const char* url = "/check_mod?username=mod&password=password123&session=session123";
    check_mod(url);
    return 0;
}