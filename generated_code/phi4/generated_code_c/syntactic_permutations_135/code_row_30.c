#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int check_mod(const char *username, const char *password) {
    // Hardcoded credentials for demonstration purposes
    const char *correct_username = "user";
    const char *correct_password = "pass";

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
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    if (check_mod(username, password)) {
        printf("Login successful.\n");
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}