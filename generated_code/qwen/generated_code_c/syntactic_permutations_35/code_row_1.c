#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

int authenticate(const char *username, const char *password) {
    // This is a mock database with one user for demonstration purposes.
    User users[] = {{"user1", "pass1"}, {"admin", "admin123"}};
    int num_users = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char *url) {
    printf("Content-Type: text/html\n");
    printf("Location: %s\n\n", url);
}

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    // Simulating form data input for demonstration purposes
    strcpy(username, "user1");
    strcpy(password, "pass1");

    if (authenticate(username, password)) {
        redirect("home.html");
    } else {
        redirect("login.html");
    }

    return 0;
}