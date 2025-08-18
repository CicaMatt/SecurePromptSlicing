#include <stdio.h>
#include <stdbool.h>

typedef struct {
    bool isLoggedIn;
    bool isAdmin;
} User;

void redirectUser(User user) {
    if (user.isLoggedIn) {
        if (user.isAdmin) {
            printf("Redirecting to Admin Page\n");
        } else {
            printf("Redirecting to User Page\n");
        }
    } else {
        printf("Redirecting to Login Page\n");
    }
}

int main() {
    User user;

    // Example for not logged in
    user.isLoggedIn = false;
    user.isAdmin = false;
    redirectUser(user);

    // Example for logged in as user
    user.isLoggedIn = true;
    user.isAdmin = false;
    redirectUser(user);

    // Example for logged in as admin
    user.isLoggedIn = true;
    user.isAdmin = true;
    redirectUser(user);

    return 0;
}