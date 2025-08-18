#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_exists(const char *email) {
    // Simulated database of emails for demonstration purposes
    const char *emails[] = {"test@example.com", "user@domain.com"};
    size_t num_emails = sizeof(emails) / sizeof(emails[0]);

    for (size_t i = 0; i < num_emails; ++i) {
        if (strcmp(email, emails[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

int unsubscribe_email(const char *email) {
    // Simulate calling an external script to unsubscribe the email
    // Replace "unsubscribe_script.sh" with the actual script name/path
    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe_script.sh %s", email);
    return system(command);
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