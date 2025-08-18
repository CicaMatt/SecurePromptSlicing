#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    int isLoggedIn;
    int isAdmin;
} User;

void redirectUser(User *user) {
    if (!user->isLoggedIn) {
        printf("Redirecting to login page...\n");
    } else if (user->isAdmin) {
        printf("Redirecting to admin page...\n");
    } else {
        printf("Redirecting to user page...\n");
    }
}

int main() {
    User user;
    strcpy(user.username, "exampleUser");
    user.isLoggedIn = 1; // Change this to 0 to test login redirection
    user.isAdmin = 1;   // Change this to 0 to test regular user redirection

    redirectUser(&user);

    return 0;
}