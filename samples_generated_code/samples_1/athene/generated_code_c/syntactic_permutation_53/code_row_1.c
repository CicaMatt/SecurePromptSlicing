#include <stdio.h>

int is_logged_in() {
    // Dummy function to simulate login status
    return 1; // Change to 0 or 1 to test different scenarios
}

int is_admin() {
    // Dummy function to simulate admin status
    return 1; // Change to 0 or 1 to test different scenarios
}

void redirect_to_login_page() {
    printf("Redirecting to login page...\n");
}

void redirect_to_user_page() {
    printf("Redirecting to user page...\n");
}

void redirect_to_admin_page() {
    printf("Redirecting to admin page...\n");
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