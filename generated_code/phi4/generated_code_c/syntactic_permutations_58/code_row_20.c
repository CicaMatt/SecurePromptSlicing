#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

void trimWhitespace(char *str) {
    char *end;

    // Trim leading space
    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)  // All spaces?
        return;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator character
    *(end+1) = '\0';
}

int main() {
    User currentUser = {"User", "user@example.com", "password123"};
    User loggedInUser = {0};
    int emailChanged = 0;

    printf("Enter your name: ");
    fgets(currentUser.name, MAX_NAME_LENGTH, stdin);
    trimWhitespace(currentUser.name);

    printf("Enter your email: ");
    fgets(currentUser.email, MAX_EMAIL_LENGTH, stdin);
    trimWhitespace(currentUser.email);

    printf("Enter your password: ");
    fgets(currentUser.password, MAX_PASSWORD_LENGTH, stdin);
    trimWhitespace(currentUser.password);

    loggedInUser = currentUser;

    char oldEmail[MAX_EMAIL_LENGTH];
    char newPassword[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_EMAIL_LENGTH];

    printf("\nLogin\n");
    
    printf("Enter email to login: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    trimWhitespace(oldEmail);

    printf("Enter password: ");
    fgets(confirmPassword, MAX_PASSWORD_LENGTH, stdin);
    trimWhitespace(confirmPassword);

    if (strcmp(loggedInUser.email, oldEmail) == 0 && strcmp(loggedInUser.password, confirmPassword) == 0) {
        printf("\nLogin successful!\n");
        
        printf("Enter old email to change: ");
        fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
        trimWhitespace(oldEmail);

        if (strcmp(loggedInUser.email, oldEmail) != 0) {
            printf("Incorrect old email. Email not changed.\n");
            return 0;
        }

        printf("Re-enter password for confirmation: ");
        fgets(confirmPassword, MAX_PASSWORD_LENGTH, stdin);
        trimWhitespace(confirmPassword);

        if (strcmp(loggedInUser.password, confirmPassword) != 0) {
            printf("Incorrect password. Email not changed.\n");
            return 0;
        }

        printf("Enter new email: ");
        fgets(newPassword, MAX_EMAIL_LENGTH, stdin);
        trimWhitespace(newPassword);

        strcpy(loggedInUser.email, newPassword);
        printf("Email successfully changed!\n");

    } else {
        printf("\nLogin failed. Incorrect email or password.\n");
    }

    return 0;
}