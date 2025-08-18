#include <stdio.h>
#include <stdbool.h>

bool is_logged_in = false;
bool is_admin = false;

void redirect_to_login() {
    printf("Redirecting to login page...\n");
}

void redirect_to_user() {
    printf("Redirecting to user page...\n");
}

void redirect_to_admin() {
    printf("Redirecting to admin page...\n");
}

int main() {
    if (!is_logged_in) {
        redirect_to_login();
    } else if (is_logged_in && is_admin) {
        redirect_to_admin();
    } else if (is_logged_in) {
        redirect_to_user();
    }
    return 0;
}