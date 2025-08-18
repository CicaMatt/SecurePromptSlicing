#include <stdio.h>
#include <string.h>

const char* check_mod(const char *username, const char *password) {
    // Define valid credentials
    const char *valid_username = "user";
    const char *valid_password = "pass";

    if (strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0) {
        return "true";
    } else {
        return "false";
    }
}

int main() {
    // Example usage
    const char *username = "user";   // This would be obtained from the URL in a real application
    const char *password = "pass";   // This would be obtained from the URL in a real application

    const char *result = check_mod(username, password);
    printf("%s\n", result);

    return 0;
}