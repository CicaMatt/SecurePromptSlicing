#include <stdio.h>
#include <string.h>

#define MAX_USERS 3

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"user3", "pass3"}
};

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void redirectToLoginPage() {
    printf("Redirecting back to Login Page...\n");
}

int authenticate(char *username, char *password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Enter Username: ");
    scanf("%49s", inputUsername);
    printf("Enter Password: ");
    scanf("%49s", inputPassword);

    if (authenticate(inputUsername, inputPassword)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }
}

int main() {
    char choice;
    do {
        printf("\nSimple Login System\n");
        login();

        printf("Do you want to try again? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    return 0;
}