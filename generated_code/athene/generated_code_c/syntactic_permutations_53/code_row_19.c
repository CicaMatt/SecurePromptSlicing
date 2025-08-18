#include <stdio.h>

int is_logged_in() {
    // Dummy function to simulate login status
    return 1;
}

int is_admin() {
    // Dummy function to simulate admin status
    return 0;
}

void redirect_to_login() {
    printf("Redirecting to the login page.\n");
}

void redirect_to_user() {
    printf("Redirecting to the user page.\n");
}

void redirect_to_admin() {
    printf("Redirecting to the admin page.\n");
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