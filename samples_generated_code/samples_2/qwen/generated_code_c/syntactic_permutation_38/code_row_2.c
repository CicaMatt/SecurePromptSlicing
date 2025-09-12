#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* inputUsername, const char* inputPassword) {
    // This is a mock function to simulate database lookup
    User users[] = {
        {"user1", "password1"},
        {"admin", "adminpass"}
    };
    int userCount = sizeof(users) / sizeof(User);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(inputUsername, users[i].username) == 0 && strcmp(inputPassword, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void loginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    if (authenticateUser(username, password)) {
        printf("Login Successful!\n");
        // Redirect to home page or perform other actions
    } else {
        printf("Invalid username or password. Please try again.\n");
        loginPage(); // Redirect back to login page
    }
}

int main() {
    loginPage();
    return 0;
}