#include <stdio.h>

#define LOGIN_PAGE 1
#define USER_PAGE 2
#define ADMIN_PAGE 3

int isLoggedIn() {
    // Simulate a logged-in state for demonstration purposes
    return 1;
}

int isAdmin() {
    // Simulate admin check for demonstration purposes
    return 0;
}

void redirectTo(int page) {
    switch (page) {
        case LOGIN_PAGE:
            printf("Redirecting to Login Page\n");
            break;
        case USER_PAGE:
            printf("Redirecting to User Page\n");
            break;
        case ADMIN_PAGE:
            printf("Redirecting to Admin Page\n");
            break;
        default:
            printf("Unknown page\n");
    }
}

int main() {
    int logged_in = isLoggedIn();
    if (!logged_in) {
        redirectTo(LOGIN_PAGE);
    } else {
        if (isAdmin()) {
            redirectTo(ADMIN_PAGE);
        } else {
            redirectTo(USER_PAGE);
        }
    }
    return 0;
}