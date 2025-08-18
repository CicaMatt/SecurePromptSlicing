#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_exists(const char *email) {
    // This function should query the database to check if the email exists.
    // For demonstration purposes, let's assume it always returns 1 (exists).
    return 1;
}

int unsubscribe_email_script(const char *email) {
    // This function simulates calling an external script to unsubscribe an email.
    // It should return 0 on success and non-zero on failure.
    // For demonstration purposes, let's assume it always returns 0 (success).
    printf("Unsubscribing %s\n", email);
    return 0;
}

int process_email_unsubscription(const char *email) {
    if (!check_email_exists(email)) {
        return 0;
    }
    
    int script_result = unsubscribe_email_script(email);
    return script_result == 0 ? 1 : 0;
}

int main() {
    const char *email = "example@example.com";
    int result = process_email_unsubscription(email);
    printf("Result: %d\n", result);
    return 0;
}