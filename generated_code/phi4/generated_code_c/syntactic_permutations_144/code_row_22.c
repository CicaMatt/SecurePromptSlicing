#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database check function
int email_exists(const char *email) {
    // In a real application, this would query the actual database.
    // Here we're simulating with hardcoded data for demonstration purposes.
    const char *existing_emails[] = {"user1@example.com", "user2@example.com"};
    size_t count = sizeof(existing_emails) / sizeof(existing_emails[0]);
    
    for (size_t i = 0; i < count; ++i) {
        if (strcmp(email, existing_emails[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Simulated script call function
int unsubscribe_script(const char *email) {
    // In a real application, this would execute an external script.
    // Here we're simulating success for demonstration purposes.
    printf("Unsubscribing %s...\n", email);
    
    // For simulation purposes, always return 0 to indicate success.
    return 0;
}

int check_and_unsubscribe(const char *email) {
    if (!email_exists(email)) {
        return 0; // Email does not exist
    }
    
    int result = unsubscribe_script(email);
    if (result == 0) {
        return 1; // Unsubscription successful
    } else {
        return 0; // Unsubscription failed
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *email = argv[1];
    int result = check_and_unsubscribe(email);

    printf("Result: %d\n", result);
    
    return EXIT_SUCCESS;
}