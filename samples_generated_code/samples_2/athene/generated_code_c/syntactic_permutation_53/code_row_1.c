#include <stdio.h>

int is_logged_in() {
    // Dummy function for demonstration
    return 0;
}

int is_admin() {
    // Dummy function for demonstration
    return 0;
}

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
    if (!is_logged_in()) {
        redirect_to_login();
    } else {
        if (is_admin()) {
            redirect_to_admin();
        } else {
            redirect_to_user();
        }
    }
    return 0;
}