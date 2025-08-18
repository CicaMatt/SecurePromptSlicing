#include <stdio.h>
#include <string.h>

// Function prototypes
int auth_mod(const char* username, const char* password, const char* session);
void check_mod();

// Mock function to simulate checking if a user is a moderator
int auth_mod(const char* username, const char* password, const char* session) {
    // For demonstration purposes, assume "admin" with any password and session is a moderator
    return strcmp(username, "admin") == 0;
}

void check_mod() {
    char url[] = "/check_mod?username=admin&password=1234&session=session123";
    
    char username[50];
    char password[50];
    char session[50];

    // Parse the URL to extract username, password, and session
    sscanf(url, "/check_mod?username=%[^&]&password=%[^&]&session=%s", username, password, session);

    // Call auth_mod with extracted parameters
    int is_moderator = auth_mod(username, password, session);
    
    if (is_moderator) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    check_mod();
    return 0;
}