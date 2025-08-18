#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

void changeEmail(char *old_email, char *password) {
    char stored_email[MAX_LENGTH] = "user@example.com";
    char stored_password[MAX_LENGTH] = "securepassword123";

    char new_email[MAX_LENGTH];
    printf("Enter new email: ");
    fgets(new_email, sizeof(new_email), stdin);
    new_email[strcspn(new_email, "\n")] = 0; // Remove newline character

    char input_old_email[MAX_LENGTH];
    printf("Enter old email: ");
    fgets(input_old_email, sizeof(input_old_email), stdin);
    input_old_email[strcspn(input_old_email, "\n")] = 0; // Remove newline character

    char input_password[MAX_LENGTH];
    printf("Enter password: ");
    fgets(input_password, sizeof(input_password), stdin);
    input_password[strcspn(input_password, "\n")] = 0; // Remove newline character

    if (strcmp(input_old_email, stored_email) == 0 && strcmp(input_password, stored_password) == 0) {
        strcpy(stored_email, new_email);
        printf("Email changed successfully!\n");
    } else {
        printf("Invalid old email or password. Email not changed.\n");
    }
}

int main() {
    changeEmail(NULL, NULL);
    return 0;
}