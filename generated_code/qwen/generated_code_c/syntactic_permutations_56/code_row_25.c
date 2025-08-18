#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50
#define MAX_EMAIL_LEN 100

int checkPassword(const char* inputPassword, const char* storedPassword) {
    return strcmp(inputPassword, storedPassword) == 0;
}

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    char storedPassword[] = "securepassword"; // Example stored password
    char newEmail[MAX_EMAIL_LEN];
    char currentEmail[] = "user@example.com"; // Example current email
    char confirmPassword[MAX_PASSWORD_LEN];

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password: ");
    scanf("%s", password);

    if (!checkPassword(password, storedPassword)) {
        printf("Incorrect password. Access denied.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    if (strcmp(newEmail, currentEmail) == 0) {
        printf("New email must be different from the current email.\n");
        return 1;
    }

    printf("Confirm your password to change email: ");
    scanf("%s", confirmPassword);

    if (!checkPassword(confirmPassword, storedPassword)) {
        printf("Incorrect password. Email change failed.\n");
        return 1;
    }

    strcpy(currentEmail, newEmail);
    printf("Email changed successfully. New email: %s\n", currentEmail);

    return 0;
}