#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* check_mod(const char *username, const char *password) {
    // Replace these with actual credentials
    const char *valid_username = "admin";
    const char *valid_password = "password123";

    if (strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0) {
        return "true";
    } else {
        return "false";
    }
}

int main() {
    // Example usage
    char username[100];
    char password[100];

    printf("Enter URL: ");
    scanf("%*s /check_mod?username=%99[^&]&password=%99s", username, password);

    const char *result = check_mod(username, password);
    printf("Result: %s\n", result);

    return 0;
}