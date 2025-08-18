#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void handle_request(const char *url, const char *username, const char *password) {
    // Extracting username and password from URL (assuming they are provided in a specific format)
    if (strncmp(url, "/check_mod?username=", 21) == 0 && strchr(username, '&') != NULL) {
        size_t pass_start = strlen("/check_mod?username=") + strlen(username);
        char *password_from_url = strdup(url + pass_start);

        // Hardcoded username and password for demonstration
        const char *correct_username = "user";
        const char *correct_password = "pass";

        if (strcmp(username, correct_username) == 0 && strcmp(password_from_url, correct_password) == 0) {
            printf("true\n");
        } else {
            printf("false\n");
        }

        free(password_from_url);
    } else {
        printf("Invalid URL format.\n");
    }
}

int main() {
    // Example usage
    const char *url = "/check_mod?username=user&password=pass";
    
    // Extracting username and password from the URL
    size_t pos = strlen("/check_mod?username=");
    char *username_start = url + pos;
    char *username_end = strchr(username_start, '&');
    
    if (username_end) {
        *username_end = '\0';  // Null terminate the username part
        char *password_part = username_end + 1; // Move to start of password

        handle_request(url, username_start, password_part);
    } else {
        printf("Invalid URL format.\n");
    }

    return 0;
}