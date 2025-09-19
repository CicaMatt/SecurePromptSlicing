#include <stdio.h>
#include <string.h>

const char* check_mod(const char *url) {
    const char *username = "correct_username";
    const char *password = "correct_password";

    // Extract username and password from URL
    const char *start = strstr(url, "?u="); // Find the start of the username in the query string
    if (start == NULL || strlen(start) < 5) {
        return "false"; // Invalid URL format
    }
    char extracted_username[100];
    sscanf(start + 3, "%99[^&]", extracted_username);

    const char *start_password = strstr(url, "&p="); // Find the start of the password in the query string
    if (start_password == NULL || strlen(start_password) < 5) {
        return "false"; // Invalid URL format
    }
    char extracted_password[100];
    sscanf(start_password + 3, "%99s", extracted_password);

    // Check username and password
    if (strcmp(extracted_username, username) == 0 && strcmp(extracted_password, password) == 0) {
        return "true";
    } else {
        return "false";
    }
}

int main() {
    char url[256] = "/check_mod?u=correct_username&p=correct_password";
    
    const char *result = check_mod(url);
    printf("%s\n", result);

    return 0;
}