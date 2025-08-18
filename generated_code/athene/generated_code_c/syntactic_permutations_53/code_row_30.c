#include <stdio.h>

int isLoggedIn();
int isAdmin();

void redirectLogin() {
    printf("Redirecting to login page...\n");
}

void redirectUserPage() {
    printf("Redirecting to user page...\n");
}

void redirectAdminPage() {
    printf("Redirecting to admin page...\n");
}

int main() {
    if (!isLoggedIn()) {
        redirectLogin();
    } else {
        if (isAdmin()) {
            redirectAdminPage();
        } else {
            redirectUserPage();
        }
    }
    return 0;
}