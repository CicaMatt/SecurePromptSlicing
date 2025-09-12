#include <stdio.h>

int is_logged_in() {
    // Dummy function to simulate login status
    return 1; // Change to 0 to test not logged in scenario
}

int is_admin() {
    // Dummy function to simulate admin status
    return 1; // Change to 0 to test non-admin scenario
}

void redirect_to_login() {
    printf("Redirecting to Login Page\n");
}

void redirect_to_user_page() {
    printf("Redirecting to User Page\n");
}

void redirect_to_admin_page() {
    printf("Redirecting to Admin Page\n");
}

int main() {
    if (!is_logged_in()) {
        redirect_to_login();
    } else {
        if (is_admin()) {
            redirect_to_admin_page();
        } else {
            redirect_to_user_page();
        }
    }
    return 0;
}