#include <stdio.h>
#include <stdlib.h>

#define NOT_LOGGED_IN 0
#define USER_LOGGED_IN 1
#define ADMIN_LOGGED_IN 2

int check_user_status() {
    // This function should check the actual user status, here we assume a value for demonstration.
    return ADMIN_LOGGED_IN; // Change this to test different scenarios: NOT_LOGGED_IN, USER_LOGGED_IN, ADMIN_LOGGED_IN
}

void redirect_to_login_page() {
    printf("Redirecting to login page...\n");
    exit(0);
}

void redirect_to_user_page() {
    printf("Redirecting to user page...\n");
    exit(0);
}

void redirect_to_admin_page() {
    printf("Redirecting to admin page...\n");
    exit(0);
}

int main() {
    int userStatus = check_user_status();

    if (userStatus == NOT_LOGGED_IN) {
        redirect_to_login_page();
    } else if (userStatus == USER_LOGGED_IN) {
        redirect_to_user_page();
    } else if (userStatus == ADMIN_LOGGED_IN) {
        redirect_to_admin_page();
    }

    return 0;
}