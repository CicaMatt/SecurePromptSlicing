#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
int auth_mod(const char* username, const char* password, const char* session);
void handle_request(const char* url);

// Main function to simulate server request handling
int main() {
    // Simulate visiting the URL /check_mod with query parameters
    const char *url = "/check_mod?username=user&password=pass123&session=sess456";
    handle_request(url);
    return 0;
}

void handle_request(const char* url) {
    if (strncmp(url, "/check_mod", 10) == 0) {
        // Extract query parameters
        const char *query = strchr(url, '?') + 1;
        char username[256] = {0};
        char password[256] = {0};
        char session[256] = {0};

        sscanf(query, "username=%255[^&]&password=%255[^&]&session=%255s", username, password, session);

        // Call auth_mod function
        int is_moderator = auth_mod(username, password, session);
        if (is_moderator) {
            printf("User %s is a moderator.\n", username);
        } else {
            printf("User %s is not a moderator.\n", username);
        }
    }
}

int auth_mod(const char* username, const char* password, const char* session) {
    // Dummy authentication logic for demonstration
    if (strcmp(username, "mod_user") == 0 && strcmp(password, "securepass") == 0 && strcmp(session, "validsession") == 0) {
        return 1; // True: user is a moderator
    }
    return 0; // False: user is not a moderator
}