#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate authentication of a moderator.
int auth_mod(const char *username, const char *password, const char *session) {
    // In real-world applications, this would involve checking a database or authentication service.
    
    // For demonstration purposes, let's assume "admin", "modpass", and "sess123" are valid credentials for a moderator
    if (strcmp(username, "admin") == 0 && strcmp(password, "modpass") == 0 && strcmp(session, "sess123") == 0) {
        return 1; // True: User is a moderator
    }
    
    return 0; // False: User is not a moderator
}

// Function to extract username, password and session from the URL.
// For simplicity, we assume the URL format is "/check_mod?username=<USERNAME>&password=<PASSWORD>&session=<SESSION>"
void parse_url(const char *url, char *username, char *password, char *session) {
    const char *start_username = strstr(url, "username=");
    const char *start_password = strstr(url, "password=");
    const char *start_session = strstr(url, "session=");

    if (start_username && start_password && start_session) {
        // Extract username
        start_username += 9; // Move past 'username='
        char *end_username = strchr(start_username, '&');
        strncpy(username, end_username ? start_username : start_username + strlen(start_username), 
                end_username ? (size_t)(end_username - start_username) : sizeof(username));
        username[end_username ? (end_username - start_username) : strlen(username)] = '\0';

        // Extract password
        start_password += 9; // Move past 'password='
        char *end_password = strchr(start_password, '&');
        strncpy(password, end_password ? start_password : start_password + strlen(start_password), 
                end_password ? (size_t)(end_password - start_password) : sizeof(password));
        password[end_password ? (end_password - start_password) : strlen(password)] = '\0';

        // Extract session
        start_session += 8; // Move past 'session='
        char *end_session = strchr(start_session, '&');
        strncpy(session, end_session ? start_session : start_session + strlen(start_session), 
                end_session ? (size_t)(end_session - start_session) : sizeof(session));
        session[end_session ? (end_session - start_session) : strlen(session)] = '\0';
    }
}

int check_mod(const char *url) {
    char username[100] = { 0 };
    char password[100] = { 0 };
    char session[100] = { 0 };

    parse_url(url, username, password, session);

    return auth_mod(username, password, session);
}

int main() {
    const char *url = "/check_mod?username=admin&password=modpass&session=sess123";

    if (check_mod(url)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }

    return 0;
}