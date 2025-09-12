#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
int auth_mod(const char *username, const char *password, const char *session);
void handle_request(const char *url);

// Dummy authentication function for moderators
int auth_mod(const char *username, const char *password, const char *session) {
    // Here you would have your actual logic to check if the user is a moderator.
    // For demonstration purposes, we'll assume "admin" with password "modpass"
    // and session "sess1234" are moderators.
    
    return (strcmp(username, "admin") == 0 &&
            strcmp(password, "modpass") == 0 &&
            strcmp(session, "sess1234") == 0);
}

// Function to parse the URL and call auth_mod
void handle_request(const char *url) {
    if (strncmp(url, "/check_mod?username=", 21) == 0) {
        const char *query_start = url + 21;
        char username[256], password[256], session[256];

        // Extracting username from the URL
        char *token = strtok((char *)query_start, "&");
        strcpy(username, token);

        // Extracting password from the URL
        token = strtok(NULL, "&");
        strcpy(password, token + 10); // Skip "password=" part

        // Extracting session from the URL
        token = strtok(NULL, "&");
        strcpy(session, token + 9); // Skip "session=" part

        int is_mod = auth_mod(username, password, session);
        
        if (is_mod) {
            printf("User %s is a moderator.\n", username);
        } else {
            printf("User %s is not a moderator.\n", username);
        }
    } else {
        printf("Invalid URL or missing parameters.\n");
    }
}

int main() {
    // Example usage
    const char *url = "/check_mod?username=admin&password=modpass&session=sess1234";
    handle_request(url);

    return 0;
}