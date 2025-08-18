#include <stdio.h>
#include <stdlib.h>

// Simulated function to check if an email exists in the database
int email_exists(const char *email) {
    // For demonstration, let's assume "user@example.com" is in the database.
    return strcmp(email, "user@example.com") == 0;
}

// Simulated function to call a script that unsubscribes the email
int unsubscribe_email(const char *email) {
    printf("Unsubscribing %s...\n", email);
    
    // For demonstration purposes, always succeed in unsubscribing.
    return system(NULL); // Replace with actual script execution logic if needed.
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *email = argv[1];

    if (!email_exists(email)) {
        printf("Email does not exist.\n");
        return 0;
    }

    int result = unsubscribe_email(email);

    if (result == 0) {
        return 1; // Script returned success
    } else {
        return 0; // Script failed or error occurred
    }
}