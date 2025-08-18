#include <stdio.h>
#include <string.h>

int check_credentials(const char *username, const char *password) {
    // Example credentials for demonstration purposes
    const char *correct_username = "admin";
    const char *correct_password = "password123";

    return strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0;
}

const char* check_mod(const char *username, const char *password) {
    if (check_credentials(username, password)) {
        return "true";
    }
    return "false";
}

int main() {
    // Simulate user input
    const char *input_username = "admin"; // Replace with actual input
    const char *input_password = "password123"; // Replace with actual input

    // Call the check_mod function
    const char* result = check_mod(input_username, input_password);

    // Print the result
    printf("%s\n", result);

    return 0;
}