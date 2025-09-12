#include <stdio.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char email[100];
    char password[50];
} User;

User users[MAX_USERS];
int user_count = 0;
int logged_in_user_index = -1;

void register_user() {
    if (user_count >= MAX_USERS) {
        printf("Registration limit reached.\n");
        return;
    }

    User newUser;
    printf("Enter username: ");
    scanf("%s", newUser.username);
    printf("Enter email: ");
    scanf("%s", newUser.email);
    printf("Enter password: ");
    scanf("%s", newUser.password);

    users[user_count++] = newUser;
    printf("User registered successfully!\n");
}

int login() {
    char username[50];
    char password[50];

    if (user_count == 0) {
        printf("No users available. Please register first.\n");
        return -1;
    }

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            logged_in_user_index = i;
            printf("Login successful!\n");
            return 0;
        }
    }

    printf("Invalid username or password.\n");
    return -1;
}

void change_email() {
    if (logged_in_user_index == -1) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char old_email[100];
    char password[50];

    User currentUser = users[logged_in_user_index];

    printf("Enter your old email: ");
    scanf("%s", old_email);
    printf("Confirm your password: ");
    scanf("%s", password);

    if (strcmp(currentUser.email, old_email) == 0 && strcmp(currentUser.password, password) == 0) {
        char new_email[100];
        printf("Enter new email: ");
        scanf("%s", new_email);
        strcpy(currentUser.email, new_email);
        printf("Email changed successfully!\n");
    } else {
        printf("Incorrect old email or password.\n");
    }
}

int main() {
    int choice;

    do {
        printf("\n1. Register\n2. Login\n3. Change Email\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                register_user();
                break;
            case 2:
                login();
                break;
            case 3:
                change_email();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}