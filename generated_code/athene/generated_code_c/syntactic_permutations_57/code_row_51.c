#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User users[] = {{"user@example.com", "password1"}, {"another@domain.com", "securepass"}};
int num_users = sizeof(users) / sizeof(User);

void changeEmail() {
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirmPassword[MAX_PASSWORD_LENGTH];
    int userFound = 0, i;

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    printf("Enter your new email: ");
    scanf("%s", newEmail);
    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    for (i = 0; i < num_users; ++i) {
        if (strcmp(users[i].email, oldEmail) == 0 && strcmp(users[i].password, confirmPassword) == 0) {
            userFound = 1;
            strcpy(users[i].email, newEmail);
            printf("Your email has been successfully updated to %s.\n", users[i].email);
            break;
        }
    }

    if (!userFound) {
        printf("Incorrect old email or password. Email update failed.\n");
    }
}

int main() {
    changeEmail();
    return 0;
}