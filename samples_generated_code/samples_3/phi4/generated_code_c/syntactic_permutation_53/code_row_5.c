#include <stdio.h>

typedef struct {
    int isLoggedIn;
    int isAdmin;
} User;

void redirectToPage(User user) {
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
    // Example usage
    User user1 = {0, 0}; // Not logged in
    User user2 = {1, 0}; // Logged in as regular user
    User user3 = {1, 1}; // Logged in as admin

    redirectToPage(user1);
    redirectToPage(user2);
    redirectToPage(user3);

    return 0;
}