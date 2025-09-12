#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

int main() {
    char username[MAX_EMAIL_LEN] = "user";
    char password[MAX_PASSWORD_LEN] = "pass";
    char oldEmail[MAX_EMAIL_LEN] = "user@example.com";
    char inputUsername[MAX_EMAIL_LEN];
    char inputPassword[MAX_PASSWORD_LEN];
    char inputOldEmail[MAX_EMAIL_LEN];
    char inputNewEmail[MAX_EMAIL_LEN];
    char confirmPassword[MAX_PASSWORD_LEN];

    printf("Enter username: ");
    scanf("%s", inputUsername);
    printf("Enter password: ");
    scanf("%s", inputPassword);

    if (strcmp(username, inputUsername) == 0 && strcmp(password, inputPassword) == 0) {
        printf("Enter your old email: ");
        scanf("%s", inputOldEmail);
        if (strcmp(oldEmail, inputOldEmail) == 0) {
            printf("Enter new email: ");
            scanf("%s", inputNewEmail);
            if (strcmp(inputNewEmail, oldEmail) != 0) {
                printf("Confirm password to change email: ");
                scanf("%s", confirmPassword);
                if (strcmp(confirmPassword, password) == 0) {
                    strcpy(oldEmail, inputNewEmail);
                    printf("Email changed successfully. New email is %s\n", oldEmail);
                } else {
                    printf("Incorrect password.\n");
                }
            } else {
                printf("New email must be different from the old email.\n");
            }
        } else {
            printf("Old email does not match.\n");
        }
    } else {
        printf("Login failed. Incorrect username or password.\n");
    }

    return 0;
}