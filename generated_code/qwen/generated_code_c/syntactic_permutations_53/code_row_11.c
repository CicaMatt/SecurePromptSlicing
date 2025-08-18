#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    int isAdmin;
} User;

int isLoggedIn(User* user) {
    return strlen(user->username) > 0;
}

void redirectUser(User* user) {
    if (!isLoggedIn(user)) {
        printf("Redirecting to login page...\n");
    } else if (user->isAdmin) {
        printf("Redirecting to admin page...\n");
    } else {
        printf("Redirecting to user page...\n");
    }
}

int main() {
    User user = {"", 0}; // Not logged in, not an admin

    printf("Initial state: ");
    redirectUser(&user);

    strcpy(user.username, "john_doe"); // Logged in, not an admin
    printf("Logged in as user: ");
    redirectUser(&user);

    user.isAdmin = 1; // Logged in and an admin
    printf("Logged in as admin: ");
    redirectUser(&user);

    return 0;
}