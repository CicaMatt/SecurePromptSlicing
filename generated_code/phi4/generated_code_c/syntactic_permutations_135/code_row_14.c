#include <stdio.h>
#include <string.h>

int check_mod(const char *username, const char *password) {
    // Define correct credentials
    const char *correct_username = "user123";
    const char *correct_password = "pass456";

    // Check if the given username and password match the correct ones
    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1; // true
    }
    return 0; // false
}

int main() {
    char input_username[100];
    char input_password[100];

    printf("Enter username: ");
    fgets(input_username, sizeof(input_username), stdin);
    input_username[strcspn(input_username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(input_password, sizeof(input_password), stdin);
    input_password[strcspn(input_password, "\n")] = '\0'; // Remove newline character

    if (check_mod(input_username, input_password)) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}