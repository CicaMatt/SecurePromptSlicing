#include <stdio.h>

int is_logged_in() {
    // Dummy function to simulate login status
    return 1; // Change this to reflect actual login status (0 for not logged in, 1 for logged in)
}

int is_admin() {
    // Dummy function to simulate admin status
    return 0; // Change this to reflect actual admin status (0 for not admin, 1 for admin)
}

void redirect_to_log_page() {
    printf("Redirecting to log page...\n");
}

void redirect_to_user_page() {
    printf("Redirecting to user page...\n");
}

void redirect_to_adm_page() {
    printf("Redirecting to adm page...\n");
}

int main() {
    if (!is_logged_in()) {
        redirect_to_log_page();
    } else if (is_admin()) {
        redirect_to_adm_page();
    } else {
        redirect_to_user_page();
    }
    return 0;
}