#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate checking if an email exists in the database
int check_email_exists(const char *email) {
    // For demonstration, let's assume "example@example.com" exists
    return strcmp(email, "example@example.com") == 0;
}

// Mock function to simulate calling a script that unsubscribes an email
int unsubscribe_email(const char *email) {
    // Simulate the script execution and return success (1)
    printf("Unsubscribing %s\n", email);
    return 1;
}

int main() {
    const char *email = "example@example.com"; // Example email to check

    if (check_email_exists(email)) {
        int result = unsubscribe_email(email);
        if (result == 1) {
            printf("Email unsubscribed successfully.\n");
        } else {
            printf("Failed to unsubscribe the email.\n");
        }
    } else {
        printf("Email does not exist in the database.\n");
    }

    return 0;
}