#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_exists(const char *email) {
    // This function should interact with your database to check if the email exists.
    // For demonstration, let's assume it always returns 1 (email exists).
    return 1;
}

int unsubscribe_script(const char *email) {
    // This function simulates calling an external script to unsubscribe the email.
    // It returns 0 on success and non-zero on failure.
    // For demonstration, let's assume it always returns 0 (success).
    printf("Unsubscribing %s\n", email);
    return 0;
}

int main() {
    const char *email = "example@example.com";

    if (!check_email_exists(email)) {
        return 0;
    }

    int result = unsubscribe_script(email);
    if (result != 0) {
        return 0;
    }

    return 1; // Indicating successful unsubscription
}