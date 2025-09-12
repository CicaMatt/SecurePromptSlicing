#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate checking if an email exists in the database
int email_exists_in_database(const char *email) {
    // For demonstration, let's assume "test@example.com" exists in the database
    return strcmp(email, "test@example.com") == 0;
}

// Mock function to simulate calling a script that unsubscribes an email
int unsubscribe_email_script(const char *email) {
    // For demonstration, let's assume the script always succeeds
    printf("Unsubscribing %s\n", email);
    return 1;
}

int main() {
    const char *email = "test@example.com";
    
    if (email_exists_in_database(email)) {
        int result = unsubscribe_email_script(email);
        if (result == 1) {
            printf("Email unsubscribed successfully.\n");
        } else {
            printf("Failed to unsubscribe email.\n");
        }
    } else {
        printf("Email does not exist in the database.\n");
    }

    return 0;
}