#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_exists(const char *email) {
    // Simulate database check
    const char *existing_emails[] = {"test@example.com", "user@example.org"};
    int num_existing_emails = sizeof(existing_emails) / sizeof(existing_emails[0]);
    
    for (int i = 0; i < num_existing_emails; ++i) {
        if (strcmp(email, existing_emails[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int unsubscribe_email(const char *email) {
    // Simulate script call
    printf("Unsubscribing email: %s\n", email);
    // Return 0 to simulate successful unsubscription
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    int email_exists = check_email_exists(email);

    if (!email_exists) {
        return 0;
    }

    int unsubscribe_result = unsubscribe_email(email);
    if (unsubscribe_result == 0) {
        return 1;
    } else {
        return 0;
    }
}