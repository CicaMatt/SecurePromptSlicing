#include <stdio.h>
#include <stdbool.h>

#define LOGGED_IN 1
#define NOT_LOGGED_IN 0
#define ADMIN_USER 1
#define NORMAL_USER 0

void login_page() {
    printf("You are not logged in.\n");
}

void user_page(int isLoggedIn) {
    if (isLoggedIn == LOGGED_IN) {
        printf("Welcome to the user page!\n");
    } else {
        login_page();
    }
}

void admin_page(int isLoggedIn, int isAdmin) {
    if (isLoggedIn == LOGGED_IN && isAdmin == ADMIN_USER) {
        printf("Welcome to the admin page!\n");
    } else {
        user_page(isLoggedIn);
    }
}

int main() {
    int isLoggedIn = NOT_LOGGED_IN;
    int isAdmin = NORMAL_USER;
    // assume the following values are obtained from a login form
    char *username = "admin";
    char *password = "password123";

    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        isLoggedIn = LOGGED_IN;
        isAdmin = ADMIN_USER;
    }

    admin_page(isLoggedIn, isAdmin);
}