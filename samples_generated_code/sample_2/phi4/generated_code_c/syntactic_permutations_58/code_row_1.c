#include <stdio.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_EMAIL 100

typedef struct {
    char username[MAX_NAME];
    char email[MAX_EMAIL];
    char password[20];
} User;

User currentUser = {"", "", ""};

int is_logged_in() {
    return strcmp(currentUser.username, "") != 0;
}

int change_email(const char *oldEmail, const char *newEmail) {
    if (!is_logged_in()) {
        printf("Error: You must be logged in to change your email.\n");
        return 0;
    }

    int password;
    do {
        printf("Enter your password (1 for correct, any other number for incorrect): ");
        scanf("%d", &password);
        if (password != 1) {
            printf("Incorrect password. Try again.\n");
        }
    } while (password != 1);

    if (strcmp(currentUser.email, oldEmail) == 0) {
        strcpy(currentUser.email, newEmail);
        printf("Email changed successfully!\n");
        return 1;
    } else {
        printf("Old email does not match the current email. Email change failed.\n");
        return 0;
    }
}

void login(const char *username, const char *email, const char *password) {
    strcpy(currentUser.username, username);
    strcpy(currentUser.email, email);
    strcpy(currentUser.password, password);
    printf("Login successful!\n");
}

int main() {
    int choice;

    do {
        printf("\n1. Login\n2. Change Email\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                char loginUsername[MAX_NAME], loginEmail[MAX_EMAIL], loginPassword[20];
                printf("Enter username: ");
                scanf("%s", loginUsername);
                printf("Enter email: ");
                scanf("%s", loginEmail);
                printf("Enter password: ");
                scanf("%s", loginPassword);

                login(loginUsername, loginEmail, loginPassword);
                break;

            case 2:
                char oldEmail[MAX_EMAIL], newEmail[MAX_EMAIL];
                printf("Enter your current email: ");
                scanf("%s", oldEmail);
                printf("Enter your new email: ");
                scanf("%s", newEmail);

                change_email(oldEmail, newEmail);
                break;

            case 3:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}