#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database for demonstration purposes
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {{"user1", "pass1"}, {"user2", "pass2"}};
int user_count = 2;

int login(const char *username, const char *password) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect_to(const char *url) {
    printf("Redirecting to %s\n", url);
}

int main() {
    // Simulated form input
    char username[50] = "user1";
    char password[50] = "pass1";

    if (login(username, password)) {
        redirect_to("/home");
    } else {
        redirect_to("/login.html");
    }

    return 0;
}