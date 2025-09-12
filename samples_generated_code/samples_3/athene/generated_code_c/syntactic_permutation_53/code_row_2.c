#include <stdio.h>

int is_authenticated() {
    return 1; // Assume user is authenticated for this example
}

int is_admin() {
    return 0; // Assume user is not an admin for this example
}

void redirect_to_login() {
    printf("Redirecting to login page.\n");
}

void redirect_to_user_page() {
    printf("Redirecting to user page.\n");
}

void redirect_to_admin_page() {
    printf("Redirecting to admin page.\n");
}

int main() {
    if (!is_authenticated()) {
        redirect_to_login();
    } else if (is_admin()) {
        redirect_to_admin_page();
    } else {
        redirect_to_user_page();
    }
    return 0;
}