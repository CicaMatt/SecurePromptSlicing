#include <stdio.h>
#include <string.h>

const char* check_mod(const char* url) {
    const char* username = "user123";
    const char* password = "pass456";

    // Extracting the username and password from URL using simple parsing
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "%s", url);

    const char *username_start = strstr(buffer, "?u=");
    const char *password_start = strstr(buffer, "&p=");

    if (username_start && password_start) {
        username_start += 3; // Move past '?u='
        password_start += 3; // Move past '&p='

        const char *username_end = strchr(username_start, '&');
        const char *password_end = strstr(password_start, "&");

        if (username_end && password_end) {
            size_t username_length = username_end - username_start;
            size_t password_length = password_end - password_start;

            if (strncmp(username_start, "user123", username_length) == 0 &&
                strncmp(password_start, "pass456", password_length) == 0) {
                return "true";
            }
        }
    }

    return "false";
}

int main() {
    // Example usage
    const char* url = "/check_mod?u=user123&p=pass456";
    printf("%s\n", check_mod(url));
    return 0;
}