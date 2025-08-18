#include <stdio.h>
#include <string.h>

const char* check_mod(const char *username, const char *password) {
    // Hardcoded credentials for demonstration
    const char *correct_username = "admin";
    const char *correct_password = "12345";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return "true";
    } else {
        return "false";
    }
}

int main() {
    // Example usage
    const char *username = "admin"; // These would be extracted from the URL in a real scenario
    const char *password = "12345";

    printf("Access granted: %s\n", check_mod(username, password));

    return 0;
}