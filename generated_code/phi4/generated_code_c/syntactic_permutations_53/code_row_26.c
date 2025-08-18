#include <stdio.h>
#include <stdlib.h>

// Dummy functions to simulate authentication states
int is_admin_logged_in() {
    // Implement actual logic here
    return 0; // Change this to 1 for testing as admin logged in
}

int is_user_logged_in() {
    // Implement actual logic here
    return 1; // Change this to 0 for testing as user not logged in
}

void redirect(const char *page) {
    printf("Redirecting to: %s\n", page);
    // In a real scenario, you would use system calls or libraries to perform the redirection.
}

int main() {
    if (is_admin_logged_in()) {
        redirect("/admin");
    } else if (is_user_logged_in()) {
        redirect("/user");
    } else {
        redirect("/login");
    }

    return 0;
}