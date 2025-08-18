#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to check if an email exists in the database
int check_email_exists(const char *email) {
    // Simulating a check: let's say "user@example.com" exists
    return strcmp(email, "user@example.com") == 0;
}

// Mock function to call unsubscribe script and get its result
int unsubscribe_script(const char *email) {
    printf("Unsubscribing email: %s\n", email);
    // Simulating the script returning 1 for success
    return 1;
}

void handle_email(const char *email) {
    if (check_email_exists(email)) {
        int result = unsubscribe_script(email);
        if (result == 1) {
            printf("Successfully unsubscribed: %s\n", email);
        } else {
            printf("Failed to unsubscribe: %s\n", email);
        }
    } else {
        printf("Email does not exist in the database: %s\n", email);
    }
}

int main() {
    const char *email_to_check = "user@example.com";
    handle_email(email_to_check);

    // Test with an email that doesn't exist
    const char *non_existent_email = "nonexistent@example.com";
    handle_email(non_existent_email);

    return 0;
}