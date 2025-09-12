#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50

typedef struct {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

User userDatabase[MAX_USERS] = {
    {"user1", "password1"},
    {"user2", "password2"},
    // Add more users as needed
};

int authenticate(const char* username, const char* password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(userDatabase[i].username, username) == 0 &&
            strcmp(userDatabase[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void loginPage() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];

    printf("Enter Username: ");
    scanf("%s", username);

    printf("Enter Password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        printf("Login successful. Redirecting to dashboard...\n");
        // Code to redirect to dashboard
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n");
        // Code to redirect back to login page
    }
}

int main() {
    loginPage();
    return 0;
}