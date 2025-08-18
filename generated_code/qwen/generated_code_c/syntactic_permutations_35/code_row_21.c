#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticate(const char* username, const char* password) {
    // This is a mock function to simulate database lookup
    User users[] = {{"user1", "pass1"}, {"user2", "pass2"}};
    int num_users = sizeof(users) / sizeof(User);

    for (int i = 0; i < num_users; ++i) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char* username, const char* password) {
    if (authenticate(username, password)) {
        printf("Redirecting to home page...\n");
        // Simulate redirect to home page
        system("echo 'Home Page' > home.html && xdg-open home.html");
    } else {
        printf("Redirecting back to login page...\n");
        // Simulate redirect to login page
        system("xdg-open login.html");
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    login(username, password);

    return 0;
}