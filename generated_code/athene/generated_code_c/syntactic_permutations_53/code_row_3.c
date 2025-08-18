#include <stdio.h>
#include <stdbool.h>

typedef struct {
    bool isLoggedIn;
    bool isAdmin;
} User;

void redirectToLogin() {
    printf("Redirecting to login page...\n");
}

void redirectToUserPage() {
    printf("Redirecting to user page...\n");
}

void redirectToAdminPage() {
    printf("Redirecting to admin page...\n");
}

void handleRedirection(User user) {
    if (!user.isLoggedIn) {
        redirectToLogin();
    } else if (user.isAdmin) {
        redirectToAdminPage();
    } else {
        redirectToUserPage();
    }
}

int main() {
    User user1 = {false, false};
    handleRedirection(user1);

    User user2 = {true, false};
    handleRedirection(user2);

    User user3 = {true, true};
    handleRedirection(user3);

    return 0;
}