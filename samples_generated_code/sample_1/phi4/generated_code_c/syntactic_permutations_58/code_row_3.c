#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
    int loggedIn;
} User;

void login(User *user) {
    printf("Enter email: ");
    fgets(user->email, MAX_EMAIL_LENGTH, stdin);
    user->email[strcspn(user->email, "\n")] = '\0';
    
    printf("Enter password: ");
    fgets(user->password, PASSWORD_LENGTH, stdin);
    user->password[strcspn(user->password, "\n")] = '\0';

    // Simulating a successful login
    strcpy(user->username, "testUser");
    user->loggedIn = 1;
}

int changeEmail(User *user) {
    if (!user->loggedIn) {
        printf("You must be logged in to change your email.\n");
        return 0;
    }

    char old_email[MAX_EMAIL_LENGTH], new_email[MAX_EMAIL_LENGTH], confirm_password[PASSWORD_LENGTH];
    
    printf("Enter old email: ");
    fgets(old_email, MAX_EMAIL_LENGTH, stdin);
    old_email[strcspn(old_email, "\n")] = '\0';
    
    if (strcmp(user->email, old_email) != 0) {
        printf("Old email is incorrect.\n");
        return 0;
    }

    printf("Enter your password: ");
    fgets(confirm_password, PASSWORD_LENGTH, stdin);
    confirm_password[strcspn(confirm_password, "\n")] = '\0';
    
    if (strcmp(user->password, confirm_password) != 0) {
        printf("Password is incorrect.\n");
        return 0;
    }

    printf("Enter new email: ");
    fgets(new_email, MAX_EMAIL_LENGTH, stdin);
    new_email[strcspn(new_email, "\n")] = '\0';
    
    strcpy(user->email, new_email);
    printf("Email changed successfully!\n");

    return 1;
}

int main() {
    User user = { .loggedIn = 0 };
    
    int choice;

    do {
        printf("\n1. Login\n2. Change Email\n3. Exit\nChoose an option: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                login(&user);
                break;
            case 2:
                changeEmail(&user);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}