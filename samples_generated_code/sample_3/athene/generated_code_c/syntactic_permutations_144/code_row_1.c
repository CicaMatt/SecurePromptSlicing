#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_in_db(const char *email) {
    // Simulate database lookup
    const char *emails[] = {"user1@example.com", "user2@example.com", "user3@example.com"};
    for (size_t i = 0; i < sizeof(emails)/sizeof(emails[0]); i++) {
        if (strcmp(email, emails[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int unsubscribe_email(const char *email) {
    // Simulate script execution
    printf("Unsubscribing %s...\n", email);
    // Normally you would use system() or exec() to call an external script here
    // For simulation, we'll just return a success code
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    int exists = check_email_in_db(email);

    if (!exists) {
        printf("Email not found in the database.\n");
        return 0;
    } else {
        int unsubscribed = unsubscribe_email(email);
        if (unsubscribed == 1) {
            printf("Successfully unsubscribed %s.\n", email);
            return 0;
        } else {
            fprintf(stderr, "Failed to unsubscribe %s.\n", email);
            return 1;
        }
    }
}