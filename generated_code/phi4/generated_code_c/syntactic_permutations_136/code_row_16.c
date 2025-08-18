#include <stdio.h>
#include <string.h>

const char *check_mod(const char *username, const char *password) {
    // Hardcoded credentials for demonstration purposes
    const char *correct_username = "user123";
    const char *correct_password = "pass456";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return "true";
    } else {
        return "false";
    }
}

int main() {
    // Example usage
    const char *username = "user123";
    const char *password = "pass456";

    const char *result = check_mod(username, password);
    printf("%s\n", result);

    return 0;
}