#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User users[] = {{"user@example.com", "password123"}};
int num_users = sizeof(users) / sizeof(users[0]);

void change_email() {
    char oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN], confirmPassword[MAX_PASSWORD_LEN];
    int found = 0, i;
    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Enter your new email: ");
    scanf("%s", newEmail);
    printf("Confirm password: ");
    scanf("%s", confirmPassword);

    for (i = 0; i < num_users; i++) {
        if (strcmp(users[i].email, oldEmail) == 0 && strcmp(users[i].password, confirmPassword) == 0) {
            found = 1;
            strcpy(users[i].email, newEmail);
            printf("Email changed successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Incorrect old email or password.\n");
    }
}

int main() {
    change_email();
    return 0;
}