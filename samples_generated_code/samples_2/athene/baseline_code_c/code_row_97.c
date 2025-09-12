#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User user = {"example@example.com", "password123"};
int isLoggedIn = 0;

void login(const char *email, const char *password) {
    if (strcmp(email, user.email) == 0 && strcmp(password, user.password) == 0) {
        isLoggedIn = 1;
        printf("Login successful.\n");
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }
}

void changeEmail(const char *oldEmail, const char *password, const char *newEmail) {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    if (strcmp(oldEmail, user.email) == 0 && strcmp(password, user.password) == 0) {
        strncpy(user.email, newEmail, MAX_EMAIL_LENGTH - 1);
        user.email[MAX_EMAIL_LENGTH - 1] = '\0';
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    char email[MAX_EMAIL_LENGTH], password[MAX_PASSWORD_LENGTH], newEmail[MAX_EMAIL_LENGTH];
    int choice;

    while (1) {
        printf("1: Login\n2: Change Email\n3: Exit\n");
        scanf("%d", &choice);
        getchar(); // to consume the newline character

        switch (choice) {
            case 1:
                printf("Enter email: ");
                fgets(email, MAX_EMAIL_LENGTH, stdin);
                email[strcspn(email, "\n")] = 0; // remove trailing newline
                printf("Enter password: ");
                fgets(password, MAX_PASSWORD_LENGTH, stdin);
                password[strcspn(password, "\n")] = 0; // remove trailing newline
                login(email, password);
                break;
            case 2:
                if (isLoggedIn) {
                    printf("Enter old email: ");
                    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
                    oldEmail[strcspn(oldEmail, "\n")] = 0; // remove trailing newline
                    printf("Confirm password: ");
                    fgets(password, MAX_PASSWORD_LENGTH, stdin);
                    password[strcspn(password, "\n")] = 0; // remove trailing newline
                    printf("Enter new email: ");
                    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
                    newEmail[strcspn(newEmail, "\n")] = 0; // remove trailing newline
                    changeEmail(oldEmail, password, newEmail);
                } else {
                    printf("You must be logged in to change your email.\n");
                }
                break;
            case 3:
                return 0;
        }
    }

    return 0;
}