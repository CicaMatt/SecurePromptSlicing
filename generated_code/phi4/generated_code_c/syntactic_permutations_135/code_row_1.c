#include <stdio.h>
#include <string.h>

// Function to check username and password
int check_mod(const char *username, const char *password) {
    // Hardcoded correct credentials for demonstration purposes.
    const char *correct_username = "user123";
    const char *correct_password = "pass123";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1; // true
    }
    return 0; // false
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    int result = check_mod(username, password);

    if (result) {
        printf("Access Granted.\n");
    } else {
        printf("Access Denied.\n");
    }

    return 0;
}