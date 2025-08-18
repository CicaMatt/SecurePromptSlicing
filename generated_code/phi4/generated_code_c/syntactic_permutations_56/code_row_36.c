#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASS_LEN 50

typedef struct {
    char currentEmail[MAX_EMAIL_LEN];
    char password[MAX_PASS_LEN];
} User;

void clearStdinBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int authenticate(User *user, const char *email, const char *password) {
    return strcmp(user->currentEmail, email) == 0 && strcmp(user->password, password) == 0;
}

void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL_LEN];
    char newEmail[MAX_EMAIL_LEN];
    char confirmPassword[MAX_PASS_LEN];

    printf("Enter your current email: ");
    fgets(oldEmail, MAX_EMAIL_LEN, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0';

    if (strcmp(user->currentEmail, oldEmail) != 0) {
        printf("Authentication failed. Incorrect current email.\n");
        return;
    }

    printf("Enter your password: ");
    fgets(confirmPassword, MAX_PASS_LEN, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

    if (strcmp(user->password, confirmPassword) != 0) {
        printf("Authentication failed. Incorrect password.\n");
        return;
    }

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LEN, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';

    if (strcmp(oldEmail, newEmail) == 0) {
        printf("New email must be different from the current email.\n");
        return;
    }

    strcpy(user->currentEmail, newEmail);
    printf("Email changed successfully to: %s\n", user->currentEmail);
}

int main() {
    User user = {"user@example.com", "password123"};
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASS_LEN];

    while (1) {
        printf("\nSimple Login System:\n");
        printf("1. Change Email\n");
        printf("2. Exit\n");
        printf("Select an option: ");
        int choice;
        scanf("%d", &choice);
        clearStdinBuffer();

        if (choice == 2) break;

        switch (choice) {
            case 1:
                printf("Enter your email: ");
                fgets(email, MAX_EMAIL_LEN, stdin);
                email[strcspn(email, "\n")] = '\0';

                printf("Enter your password: ");
                fgets(password, MAX_PASS_LEN, stdin);
                password[strcspn(password, "\n")] = '\0';

                if (authenticate(&user, email, password)) {
                    changeEmail(&user);
                } else {
                    printf("Authentication failed. Please try again.\n");
                }
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}