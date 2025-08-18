#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Mock database for demonstration purposes
struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

int authenticateUser(const char* username, const char* password) {
    struct User user = {"admin", "password123"};
    return strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0;
}

void redirect(char* url) {
    printf("Redirecting to %s...\n", url);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character from the input
    username[strcspn(username, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    // Remove newline character from the input
    password[strcspn(password, "\n")] = '\0';

    if (authenticateUser(username, password)) {
        redirect("/dashboard");
    } else {
        redirect("/login");
    }

    return 0;
}