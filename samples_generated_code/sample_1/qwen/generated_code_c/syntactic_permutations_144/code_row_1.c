#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_exists(const char *email) {
    // Simulated function to check if an email exists in the database
    // Return 1 if the email exists, 0 otherwise
    const char *existing_emails[] = {"example@example.com", "test@test.com"};
    for (size_t i = 0; i < sizeof(existing_emails) / sizeof(existing_emails[0]); ++i) {
        if (strcmp(email, existing_emails[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int call_unsubscribe_script(const char *email) {
    // Simulated function to call the unsubscribe script
    // Return 1 if the script succeeds, 0 otherwise
    printf("Unsubscribing email: %s\n", email);
    // Here you would typically system() or popen() to call an external script
    return 1; // Simulating success
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *email = argv[1];
    if (check_email_exists(email)) {
        int result = call_unsubscribe_script(email);
        if (result) {
            printf("Email unsubscribed successfully.\n");
        } else {
            printf("Failed to unsubscribe email.\n");
        }
    } else {
        printf("Email does not exist in the database.\n");
    }

    return EXIT_SUCCESS;
}