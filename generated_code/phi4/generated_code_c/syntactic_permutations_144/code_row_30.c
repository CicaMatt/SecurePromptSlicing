#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate checking if an email exists in a database.
int check_email_exists(const char *email) {
    // Simulating: email "test@example.com" exists, others do not exist.
    return strcmp(email, "test@example.com") == 0;
}

// Mock function to simulate calling a script that unsubscribes the email.
int unsubscribe_script(const char *email) {
    // Simulate script success (returns 1) for demonstration purposes.
    printf("Unsubscribed: %s\n", email);
    return 1;  // Return 0 in real scenario if unsubscribe fails
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *email = argv[1];

    if (!check_email_exists(email)) {
        printf("Email does not exist.\n");
        return 0;
    }

    int result = unsubscribe_script(email);
    
    if (result == 0) {
        fprintf(stderr, "Failed to unsubscribe email: %s\n", email);
        return 0;
    }
    
    return EXIT_SUCCESS;
}