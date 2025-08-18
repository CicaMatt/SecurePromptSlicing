#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define PASSWORD_LEN 20
#define EMAIL_LEN 50

typedef struct {
    char username[50];
    char email[EMAIL_LEN];
    char password[PASSWORD_LEN];
} User;

User users[MAX_USERS] = {
    {"user1", "oldemail1@example.com", "password1"},
    {"user2", "oldemail2@example.com", "password2"}
};
int userCount = 2;
int loggedInIndex = -1;

void displayMenu() {
    printf("\n--- Login System Menu ---\n");
    printf("1. Login\n");
    printf("2. Change Email (Must be logged in)\n");
    printf("3. Logout\n");
    printf("4. Exit\n");
}

int findUserIndexByUsername(char *username) {
    for(int i = 0; i < userCount; i++) {
        if(strcmp(users[i].username, username) == 0) {
            return i;
        }
    }
    return -1;
}

void login() {
    char username[50], password[PASSWORD_LEN];
    
    printf("Enter username: ");
    scanf("%49s", username);
    int index = findUserIndexByUsername(username);

    if(index != -1) {
        printf("Enter password: ");
        scanf("%19s", password);

        if(strcmp(users[index].password, password) == 0) {
            loggedInIndex = index;
            printf("Login successful!\n");
        } else {
            printf("Incorrect password.\n");
        }
    } else {
        printf("User not found.\n");
    }
}

void changeEmail() {
    if(loggedInIndex == -1) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[EMAIL_LEN], password[PASSWORD_LEN];
    
    printf("Enter old email: ");
    scanf("%49s", oldEmail);
    printf("Confirm password: ");
    scanf("%19s", password);

    if(strcmp(users[loggedInIndex].email, oldEmail) == 0 && strcmp(users[loggedInIndex].password, password) == 0) {
        char newEmail[EMAIL_LEN];
        printf("Enter new email: ");
        scanf("%49s", newEmail);
        strcpy(users[loggedInIndex].email, newEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Old email or password is incorrect.\n");
    }
}

void logout() {
    if(loggedInIndex != -1) {
        loggedInIndex = -1;
        printf("Logged out successfully!\n");
    } else {
        printf("You are not logged in.\n");
    }
}

int main() {
    int choice;

    while(1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                login();
                break;
            case 2:
                changeEmail();
                break;
            case 3:
                logout();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}