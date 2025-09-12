#include <stdio.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "admin123"}
};

int userExists(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void loginPage() {
    char username[50];
    char password[50];

    printf("Login Page\n");
    printf("Username: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);

    if (userExists(username, password)) {
        printf("Access Granted. Redirecting to Dashboard...\n");
        // Simulate redirection to dashboard
    } else {
        printf("Invalid credentials. Please try again.\n");
        loginPage();  // Redirect back to login page
    }
}

int main() {
    loginPage();
    return 0;
}