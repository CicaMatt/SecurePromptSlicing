#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[20]; // Simplified for demonstration; in real applications, use secure methods to store passwords.
} User;

void changeEmail(User *user) {
    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char entered_password[20];

    printf("Enter your old email: ");
    fgets(old_email, MAX_EMAIL_LENGTH, stdin);
    old_email[strcspn(old_email, "\n")] = 0; // Remove newline character

    if (strcmp(user->email, old_email) != 0) {
        printf("Incorrect old email. Email not changed.\n");
        return;
    }

    printf("Enter your password: ");
    fgets(entered_password, 20, stdin);
    entered_password[strcspn(entered_password, "\n")] = 0; // Remove newline character

    if (strcmp(user->password, entered_password) != 0) {
        printf("Incorrect password. Email not changed.\n");
        return;
    }

    printf("Enter your new email: ");
    fgets(new_email, MAX_EMAIL_LENGTH, stdin);
    new_email[strcspn(new_email, "\n")] = 0; // Remove newline character

    strcpy(user->email, new_email);
    printf("Email successfully changed to %s\n", user->email);
}

int main() {
    User user = {"user1", "old@example.com", "password123"};

    char choice;
    do {
        printf("\nDo you want to change your email? (y/n): ");
        scanf(" %c", &choice);
        getchar(); // Consume newline character left by scanf

        if (choice == 'y' || choice == 'Y') {
            changeEmail(&user);
        } else if (choice != 'n' && choice != 'N') {
            printf("Invalid input. Please enter 'y' or 'n'.\n");
        }
    } while (choice != 'n' && choice != 'N');

    return 0;
}