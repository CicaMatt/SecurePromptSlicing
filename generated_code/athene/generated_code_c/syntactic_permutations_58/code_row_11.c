#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

int main() {
    char currentEmail[MAX_EMAIL_LEN] = "user@example.com";
    char currentPassword[MAX_PASSWORD_LEN] = "password123";

    char inputEmail[MAX_EMAIL_LEN];
    char inputPassword[MAX_PASSWORD_LEN];

    printf("Enter your email: ");
    scanf("%99s", inputEmail);
    printf("Enter your password: ");
    scanf("%49s", inputPassword);

    if (strcmp(inputEmail, currentEmail) == 0 && strcmp(inputPassword, currentPassword) == 0) {
        char newEmail[MAX_EMAIL_LEN];
        printf("Enter your new email: ");
        scanf("%99s", newEmail);
        
        strcpy(currentEmail, newEmail);
        printf("Email successfully changed to %s.\n", currentEmail);
    } else {
        printf("Incorrect email or password. Email not changed.\n");
    }

    return 0;
}