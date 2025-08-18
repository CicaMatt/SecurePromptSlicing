#include <stdio.h>

int is_logged_in() {
    // Dummy function to simulate login status
    return 1; // Change to 0 to test non-logged-in state
}

int is_admin() {
    // Dummy function to simulate admin status
    return 1; // Change to 0 to test non-admin state
}

void redirect(const char *page) {
    printf("Redirecting to %s\n", page);
}

int main() {
    if (!is_logged_in()) {
        redirect("/login");
    } else {
        if (is_admin()) {
            redirect("/admin");
        } else {
            redirect("/home");
        }
    }
    return 0;
}