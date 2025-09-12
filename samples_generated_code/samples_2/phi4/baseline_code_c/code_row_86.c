#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User usersDatabase[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

int checkLogin(const char* username, const char* password) {
    int numUsers = sizeof(usersDatabase) / sizeof(usersDatabase[0]);
    for (int i = 0; i < numUsers; ++i) {
        if (strcmp(usersDatabase[i].username, username) == 0 && 
            strcmp(usersDatabase[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirectTo(const char* page) {
    printf("Redirecting to %s\n", page);
}

int main() {
    char formUsername[50];
    char formPassword[50];

    // Simulating form data from login.html
    printf("Enter username: ");
    fgets(formUsername, sizeof(formUsername), stdin);
    formUsername[strcspn(formUsername, "\n")] = 0;  // Remove newline character

    printf("Enter password: ");
    fgets(formPassword, sizeof(formPassword), stdin);
    formPassword[strcspn(formPassword, "\n")] = 0;  // Remove newline character

    if (checkLogin(formUsername, formPassword)) {
        redirectTo("/home.html");
    } else {
        redirectTo("/login.html");
    }

    return 0;
}