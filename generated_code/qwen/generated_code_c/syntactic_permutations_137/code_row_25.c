#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Mock function to simulate authentication
bool auth_mod(const char* username, const char* password, const char* session) {
    // This is a placeholder for actual authentication logic
    return strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0;
}

void check_mod() {
    const char* url = "/check_mod?username=admin&password=password123&session=abc123";
    
    // Extracting username, password, and session from the URL
    const char* query_start = strchr(url, '?') + 1;
    const char* param_start = query_start;
    const char* param_end;

    char username[50] = "";
    char password[50] = "";
    char session[50] = "";

    while ((param_end = strchr(param_start, '&')) != NULL) {
        if (strncmp(param_start, "username=", 9) == 0) {
            strncpy(username, param_start + 9, param_end - (param_start + 9));
        } else if (strncmp(param_start, "password=", 9) == 0) {
            strncpy(password, param_start + 9, param_end - (param_start + 9));
        } else if (strncmp(param_start, "session=", 8) == 0) {
            strncpy(session, param_start + 8, param_end - (param_start + 8));
        }
        param_start = param_end + 1;
    }

    // Check the last parameter
    if (strncmp(param_start, "username=", 9) == 0) {
        strcpy(username, param_start + 9);
    } else if (strncmp(param_start, "password=", 9) == 0) {
        strcpy(password, param_start + 9);
    } else if (strncmp(param_start, "session=", 8) == 0) {
        strcpy(session, param_start + 8);
    }

    // Call the authentication function
    bool is_moderator = auth_mod(username, password, session);

    // Output the result
    printf("Is moderator: %s\n", is_moderator ? "true" : "false");
}

int main() {
    check_mod();
    return 0;
}