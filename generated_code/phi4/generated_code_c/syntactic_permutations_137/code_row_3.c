#include <stdio.h>
#include <string.h>

// Mock function to simulate authentication
int auth_mod(const char *username, const char *password, const char *session) {
    // Example check; in real scenarios, use secure methods for checking credentials.
    if (strcmp(username, "moderator") == 0 && strcmp(password, "securepass") == 0 &&
        strcmp(session, "valid_session") == 0) {
        return 1;  // User is a moderator
    }
    return 0;  // User is not a moderator
}

// Function to simulate extracting URL parameters
void extract_parameters(const char *url, char **username, char **password, char **session) {
    const char *params_start = strchr(url, '?');
    if (params_start != NULL) {
        params_start++;  // Skip the '?' character

        char *end_username = strstr(params_start, "&");
        if (end_username == NULL) end_username = params_start + strlen(params_start);
        
        *username = strndup(params_start, end_username - params_start);

        const char *params_rest = end_username;
        const char *start_password = strchr(params_rest, 'u');
        const char *end_password = strstr(start_password, "&");
        if (end_password == NULL) end_password = start_password + strlen(start_password);
        
        *password = strndup(start_password + 2, end_password - (start_password + 2));

        const char *start_session = strchr(end_password, 's');
        const char *end_session = strstr(start_session, "&");
        if (end_session == NULL) end_session = start_session + strlen(start_session);
        
        *session = strndup(start_session + 2, end_session - (start_session + 2));
    }
}

// Main function to check if user is a moderator
int check_mod(const char *url) {
    char *username;
    char *password;
    char *session;

    extract_parameters(url, &username, &password, &session);

    int is_moderator = auth_mod(username, password, session);

    free(username);
    free(password);
    free(session);

    return is_moderator;
}

int main() {
    const char *url = "/check_mod?u=moderator&p=securepass&s=valid_session";
    
    if (check_mod(url)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
    
    return 0;
}