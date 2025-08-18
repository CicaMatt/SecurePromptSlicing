#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char *username, const char *password) {
    // Simulated database of users
    User database[] = {
        {"user1", "pass1"},
        {"user2", "pass2"}
    };
    int userCount = sizeof(database) / sizeof(User);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void loginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (authenticateUser(username, password)) {
        printf("Login successful. Redirecting to Dashboard...\n");
        // Here you would typically redirect to a dashboard page
    } else {
        printf("Invalid username or password. Redirecting back to Login Page...\n");
        loginPage();
    }
}

int main() {
    printf("Welcome to the Application\n");
    loginPage();
    return 0;
}