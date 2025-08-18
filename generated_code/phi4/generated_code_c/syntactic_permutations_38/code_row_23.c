#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User users_db[] = {
    {"user1", "password1"},
    {"user2", "password2"},
};

int authenticate(const char *username, const char *password) {
    for (size_t i = 0; i < sizeof(users_db) / sizeof(User); i++) {
        if (strcmp(users_db[i].username, username) == 0 &&
            strcmp(users_db[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
    system(url); // Simulates a redirection
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        username[strcspn(username, "\n")] = '\0';  // Remove newline character
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        password[strcspn(password, "\n")] = '\0';  // Remove newline character
    }

    if (authenticate(username, password)) {
        redirect("./dashboard.html");  // Assume dashboard.html is the success page
    } else {
        printf("Invalid username or password.\n");
        redirect("./login.html");  // Redirect back to login page
    }

    return 0;
}