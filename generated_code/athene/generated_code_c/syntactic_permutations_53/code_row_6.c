#include <stdio.h>

int is_logged_in() {
    // Dummy function to simulate login status
    return 1; // Change this to 0 or 1 based on actual logic
}

int is_admin() {
    // Dummy function to simulate admin status
    return 0; // Change this to 0 or 1 based on actual logic
}

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    if (!is_logged_in()) {
        redirect("/login");
    } else if (is_admin()) {
        redirect("/admin");
    } else {
        redirect("/user");
    }
    return 0;
}