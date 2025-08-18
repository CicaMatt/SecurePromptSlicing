#include <stdio.h>
#include <string.h>

// Function prototypes
int check_mod(const char *username, const char *password);

int main(void) {
    // Example usage
    const char *input_username = "user123";
    const char *input_password = "pass123";

    if (check_mod(input_username, input_password)) {
        printf("Login successful.\n");
    } else {
        printf("Login failed.\n");
    }

    return 0;
}

// Function to check username and password
int check_mod(const char *username, const char *password) {
    // Hardcoded correct credentials for demonstration purposes.
    const char *correct_username = "user123";
    const char *correct_password = "pass123";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1; // Return true
    } else {
        return 0; // Return false
    }
}