#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

// Mock database of users
User userDatabase[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};
const int userCount = sizeof(userDatabase) / sizeof(User);

int login(char *username, char *password) {
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(userDatabase[i].username, username) == 0 &&
            strcmp(userDatabase[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirectTo(const char *url) {
    printf("Redirecting to: %s\n", url);
    // In a real web server, you would use HTTP headers for redirection.
}

int main() {
    char username[50], password[50];

    // Simulating form input
    printf("Enter username: ");
    scanf("%49s", username);  // Limiting to prevent buffer overflow

    printf("Enter password: ");
    scanf("%49s", password);

    if (login(username, password)) {
        redirectTo("/home.html");
    } else {
        redirectTo("/login.html");
    }

    return 0;
}