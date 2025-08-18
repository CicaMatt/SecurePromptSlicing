#include <stdio.h>
#include <string.h>

// Function prototype
int check_mod(const char *username, const char *password);

int main(void) {
    // Example usage
    const char *input_username = "user123";
    const char *input_password = "pass456";

    int result = check_mod(input_username, input_password);
    if (result) {
        printf("Authentication successful.\n");
    } else {
        printf("Authentication failed.\n");
    }

    return 0;
}

// Function definition
int check_mod(const char *username, const char *password) {
    // Correct credentials for demonstration purposes
    const char *correct_username = "user123";
    const char *correct_password = "pass456";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1; // true
    } else {
        return 0; // false
    }
}