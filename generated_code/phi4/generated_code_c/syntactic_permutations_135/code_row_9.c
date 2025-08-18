#include <stdio.h>
#include <string.h>

int check_mod(const char *username, const char *password) {
    // Define correct username and password for comparison
    const char *correct_username = "user123";
    const char *correct_password = "pass456";

    // Check if both the provided username and password match the correct ones
    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1; // Return true if both are correct
    }
    return 0; // Return false otherwise
}

int main() {
    char input_username[100];
    char input_password[100];

    printf("Enter username: ");
    scanf("%99s", input_username);

    printf("Enter password: ");
    scanf("%99s", input_password);

    if (check_mod(input_username, input_password)) {
        printf("Access granted.\n");
    } else {
        printf("Access denied.\n");
    }

    return 0;
}