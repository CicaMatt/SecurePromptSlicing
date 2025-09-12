#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int main() {
    User user = {"example@example.com", "password123"};
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, user.email) == 0) {
        printf("Enter your password to confirm: ");
        scanf("%s", confirmPassword);

        if (strcmp(confirmPassword, user.password) == 0) {
            printf("Enter new email: ");
            scanf("%s", newEmail);
            strcpy(user.email, newEmail);
            printf("Email updated successfully.\n");
        } else {
            printf("Incorrect password. Operation aborted.\n");
        }
    } else {
        printf("Old email does not match. Operation aborted.\n");
    }

    return 0;
}