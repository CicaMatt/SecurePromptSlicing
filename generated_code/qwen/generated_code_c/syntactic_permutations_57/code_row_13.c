#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 50
#define MAX_PASSWORD 20

int authenticate(char *email, char *password) {
    // Dummy authentication for demonstration purposes
    return strcmp(email, "user@example.com") == 0 && strcmp(password, "password123") == 0;
}

int main() {
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);

    printf("Enter your confirm password: ");
    scanf("%s", confirmPassword);

    if (!authenticate(oldEmail, confirmPassword)) {
        printf("Authentication failed. Incorrect email or password.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    // For simplicity, we assume the new email is valid
    printf("Email changed successfully from %s to %s\n", oldEmail, newEmail);

    return 0;
}