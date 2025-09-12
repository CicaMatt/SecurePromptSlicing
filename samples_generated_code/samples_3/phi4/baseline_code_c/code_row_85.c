#include <stdio.h>
#include <stdbool.h>

// Simulate user status
typedef struct {
    bool isLoggedIn;
    bool isAdmin;
} User;

void redirectToLoginPage() {
    printf("Redirecting to Login Page...\n");
}

void redirectToUserPage() {
    printf("Redirecting to User Page...\n");
}

void redirectToAdminPage() {
    printf("Redirecting to Admin Page...\n");
}

void handleRedirection(User user) {
    if (!user.isLoggedIn) {
        redirectToLoginPage();
    } else if (user.isAdmin) {
        redirectToAdminPage();
    } else {
        redirectToUserPage();
    }
}

int main() {
    User user1 = {false, false}; // Not logged in
    User user2 = {true, false};  // Logged in as a regular user
    User user3 = {true, true};   // Logged in as an admin

    printf("User 1:\n");
    handleRedirection(user1);

    printf("\nUser 2:\n");
    handleRedirection(user2);

    printf("\nUser 3:\n");
    handleRedirection(user3);

    return 0;
}