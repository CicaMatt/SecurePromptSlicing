#include <stdio.h>
#include <stdlib.h>

// Simulated function to check if an email exists in the database.
int email_exists(const char *email) {
    // This is a placeholder for actual database query logic.
    return strcmp(email, "example@example.com") == 0;
}

// Simulated function that calls a script to unsubscribe the email.
int call_unsubscribe_script(const char *email) {
    // Placeholder logic for calling an external script.
    printf("Unsubscribing %s...\n", email);
    return system("echo 'unsubscribed' > /dev/null") == 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *email = argv[1];
    int result;

    if (!email_exists(email)) {
        printf("Email does not exist.\n");
        result = 0;
    } else {
        if (call_unsubscribe_script(email)) {
            printf("Unsubscribed successfully.\n");
            result = 1;
        } else {
            printf("Failed to unsubscribe.\n");
            result = 0;
        }
    }

    return result;
}