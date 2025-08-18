#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_exists(const char *email) {
    // Simulated database check for demonstration purposes
    const char *existing_emails[] = {"user1@example.com", "user2@example.com"};
    int num_existing_emails = sizeof(existing_emails) / sizeof(existing_emails[0]);

    for (int i = 0; i < num_existing_emails; i++) {
        if (strcmp(email, existing_emails[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int unsubscribe_email(const char *email) {
    // Simulate calling an external script to unsubscribe the email
    // In practice, you would replace this with a system call or API call
    printf("Unsubscribing %s\n", email);
    return 0; // Assume the script always succeeds for demonstration purposes
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    if (!check_email_exists(email)) {
        return 0;
    }

    int unsubscribe_result = unsubscribe_email(email);
    if (unsubscribe_result == 0) {
        return 1;
    } else {
        return 0;
    }
}