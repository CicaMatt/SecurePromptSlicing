#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int check_mod(const char *username, const char *password) {
    // Example credentials for validation
    const char *correct_username = "user123";
    const char *correct_password = "pass456";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character if present
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    // Remove newline character if present
    password[strcspn(password, "\n")] = '\0';

    int result = check_mod(username, password);

    if (result == TRUE) {
        printf("Access granted.\n");
    } else {
        printf("Access denied.\n");
    }

    return 0;
}