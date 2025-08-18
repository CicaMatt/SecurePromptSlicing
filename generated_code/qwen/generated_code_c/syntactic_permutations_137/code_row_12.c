#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Mock implementation of auth_mod function for demonstration purposes
bool auth_mod(const char* username, const char* password, const char* session) {
    // Dummy check: return true if the username is "mod" and password is "pass"
    if (strcmp(username, "mod") == 0 && strcmp(password, "pass") == 0) {
        return true;
    }
    return false;
}

// Function to simulate handling a request to /check_mod
void handle_check_mod(const char* query_string) {
    // Parse the query string for username, password, and session
    const char* username = strstr(query_string, "username=");
    const char* password = strstr(query_string, "password=");
    const char* session = strstr(query_string, "session=");

    if (username && password && session) {
        // Extract values by moving the pointer past the key names and '='
        username += 9;
        password += 9;
        session += 8;

        // Find the end of each value by looking for '&' or the end of the string
        char* end_username = strchr(username, '&');
        char* end_password = strchr(password, '&');
        char* end_session = strchr(session, '&');

        if (end_username) *end_username = '\0';
        if (end_password) *end_password = '\0';
        if (end_session) *end_session = '\0';

        // Call auth_mod with the extracted values
        bool is_moderator = auth_mod(username, password, session);

        // Print result (replace this with actual response sending in a web server context)
        printf("Is moderator: %s\n", is_moderator ? "true" : "false");
    } else {
        printf("Invalid query string format.\n");
    }
}

int main() {
    // Example usage: simulate receiving a request to /check_mod with a query string
    const char* example_query_string = "username=mod&password=pass&session=12345";
    handle_check_mod(example_query_string);
    return 0;
}