#include <stdio.h>

#define LOGGED_IN 1
#define ADMIN 1

void redirect_to_login() {
    printf("Redirecting to login page.\n");
}

void redirect_to_user() {
    printf("Redirecting to user page.\n");
}

void redirect_to_admin() {
    printf("Redirecting to admin page.\n");
}

int main() {
    int is_logged_in = LOGGED_IN;
    int is_admin = ADMIN;

    if (!is_logged_in) {
        redirect_to_login();
    } else if (is_admin) {
        redirect_to_admin();
    } else {
        redirect_to_user();
    }

    return 0;
}