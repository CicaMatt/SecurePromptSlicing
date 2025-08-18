#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declaration
int auth_mod(const char *name, const char *password, const char *session);

void handle_request(const char *url) {
    // Simulating URL parsing (very basic)
    if (strncmp(url, "/check_mod?name=", 16) == 0) {
        const char *params = url + 16;
        char name[256], password[256], session[256];
        
        sscanf(params, "name=%[^&]&password=%[^&]&session=%s", name, password, session);
        
        if (auth_mod(name, password, session)) {
            printf("User is a moderator.\n");
        } else {
            printf("User is not a moderator.\n");
        }
    } else {
        printf("Invalid URL\n");
    }
}

// Simulated authentication function
int auth_mod(const char *name, const char *password, const char *session) {
    // Replace with actual verification logic
    if (strcmp(name, "moderator") == 0 && strcmp(password, "pass123") == 0 &&
        strcmp(session, "valid_session") == 0) {
        return 1; // True: is a moderator
    }
    return 0; // False: not a moderator
}

int main() {
    // Simulate visiting the URL with parameters
    handle_request("/check_mod?name=moderator&password=pass123&session=valid_session");
    handle_request("/check_mod?name=user&password=wrong_pass&session=invalid_session");

    return 0;
}