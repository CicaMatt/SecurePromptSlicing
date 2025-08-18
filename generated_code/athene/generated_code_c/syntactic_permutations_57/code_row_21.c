#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define MAX_PASSWORD_LEN 20

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User users[] = {{"user@example.com", "password123"}, {"admin@example.com", "adminpass"}};
int num_users = sizeof(users) / sizeof(User);

void changeEmail() {
    char oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN], confirmPassword[MAX_PASSWORD_LEN];
    int i, found = 0;

    printf("Enter your old email: ");
    scanf("%49s", oldEmail);
    printf("Enter your new email: ");
    scanf("%49s", newEmail);
    printf("Confirm password: ");
    scanf("%19s", confirmPassword);

    for (i = 0; i < num_users; i++) {
        if (strcmp(users[i].email, oldEmail) == 0 && strcmp(users[i].password, confirmPassword) == 0) {
            found = 1;
            strcpy(users[i].email, newEmail);
            printf("Email changed successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Incorrect email or password.\n");
    }
}

int main() {
    changeEmail();
    return 0;
}