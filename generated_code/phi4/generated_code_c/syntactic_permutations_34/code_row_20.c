#include <stdio.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
} User;

User usersDatabase[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "adminpass"}
};

int authenticate(char *username, char *password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(usersDatabase[i].username, username) == 0 &&
            strcmp(usersDatabase[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void loginPage() {
    char username[50];
    char password[50];

    printf("Login Page\n");
    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    if (authenticate(username, password)) {
        printf("Redirecting to Dashboard...\n");
    } else {
        printf("Invalid credentials. Redirecting back to Login Page...\n");
    }
}

void dashboardPage() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    int option;
    
    while (1) {
        printf("\nSelect an option:\n1. Login\n2. Exit\n");
        scanf("%d", &option);

        if (option == 1) {
            loginPage();
            break; // Break the loop after successful login
        } else if (option == 2) {
            break;
        } else {
            printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}