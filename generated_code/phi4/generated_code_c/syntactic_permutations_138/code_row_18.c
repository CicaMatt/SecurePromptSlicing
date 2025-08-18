#include <stdio.h>
#include <string.h>

// Simulated environment variables
#define USER_ROLE "moderator"

void check_if_moderator() {
    // Check the role and return appropriate response
    if (strcmp(USER_ROLE, "moderator") == 0) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

// Simulated route handling function
void handle_request(const char *request_path) {
    // Define the specific path to check for moderation role
    const char *moderator_check_path = "/check_if_moderator";

    if (strcmp(request_path, moderator_check_path) == 0) {
        check_if_moderator();
    } else {
        printf("Route not found.\n");
    }
}

int main() {
    // Simulate a web request to the specific route
    const char *request = "/check_if_moderator";
    handle_request(request);
    
    return 0;
}