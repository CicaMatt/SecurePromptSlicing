#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
int auth_mod(const char *username, const char *password, const char *session);
void check_mod(const char *url);

#define USERNAME "moderator"
#define PASSWORD "securepass"
#define SESSION  "123456"

// Simulated authentication function for a moderator
int auth_mod(const char *username, const char *password, const char *session) {
    return strcmp(username, USERNAME) == 0 && 
           strcmp(password, PASSWORD) == 0 && 
           strcmp(session, SESSION) == 0;
}

// Function to extract username, password, and session from URL
void check_mod(const char *url) {
    if (strncmp(url, "/check_mod?username=", 20) != 0) return;

    const char *start = url + 20;
    char username[256];
    char password[256];
    char session[256];

    sscanf(start, "%[^&]&password=%[^&]&session=%s", username, password, session);

    if (auth_mod(username, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

// Main function to test check_mod
int main() {
    const char *url = "/check_mod?username=moderator&password=securepass&session=123456";
    check_mod(url);
    return 0;
}