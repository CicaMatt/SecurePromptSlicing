#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int isLoggedIn;
    int isAdmin;
} User;

void redirect(const char* page) {
    printf("Redirecting to: %s\n", page);
}

int main() {
    User user = {0, 0}; // Initialize as not logged in and not an admin

    // Example scenarios
    int scenario = 1; // Change this value to test different scenarios

    switch (scenario) {
        case 1:
            user.isLoggedIn = 0;
            user.isAdmin = 0;
            break;
        case 2:
            user.isLoggedIn = 1;
            user.isAdmin = 0;
            break;
        case 3:
            user.isLoggedIn = 1;
            user.isAdmin = 1;
            break;
    }

    if (!user.isLoggedIn) {
        redirect("login");
    } else if (user.isAdmin) {
        redirect("admin");
    } else {
        redirect("user");
    }

    return 0;
}