#include <stdio.h>
#include <stdlib.h>

// Mock function to simulate checking if an email exists in the database.
int email_exists(const char *email) {
    // For demonstration purposes, let's assume "test@example.com" is the only existing email.
    return (strcmp(email, "test@example.com") == 0);
}

// Mock function to simulate calling a script to unsubscribe an email.
int call_unsubscribe_script(const char *email) {
    // For demonstration purposes, let's assume the script always succeeds.
    printf("Unsubscribing %s...\n", email);
    return 1; // Simulate success
}

int check_and_unsubscribe_email(const char *email) {
    if (!email_exists(email)) {
        return 0;
    }

    int result = call_unsubscribe_script(email);

    return (result == 1) ? 1 : 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *email = argv[1];
    int result = check_and_unsubscribe_email(email);

    printf("Result: %d\n", result);
    return EXIT_SUCCESS;
}