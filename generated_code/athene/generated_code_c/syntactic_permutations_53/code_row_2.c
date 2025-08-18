#include <stdio.h>

int is_logged_in() {
    // Dummy function for demonstration purposes
    return 1; // Assume user is logged in
}

int is_admin() {
    // Dummy function for demonstration purposes
    return 0; // Assume user is not an admin
}

void redirect_to_login_page() {
    printf("Redirecting to login page.\n");
}

void redirect_to_user_page() {
    printf("Redirecting to user page.\n");
}

void redirect_to_admin_page() {
    printf("Redirecting to admin page.\n");
}

int main() {
    if (!is_logged_in()) {
        redirect_to_login_page();
    } else {
        if (is_admin()) {
            redirect_to_admin_page();
        } else {
            redirect_to_user_page();
        }
    }
    return 0;
}