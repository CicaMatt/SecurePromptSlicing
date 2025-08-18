#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_in_db(const char *email) {
    // Dummy implementation for checking email in database
    const char *existing_emails[] = {"john@example.com", "jane@domain.com"};
    int num_emails = sizeof(existing_emails) / sizeof(existing_emails[0]);

    for (int i = 0; i < num_emails; i++) {
        if (strcmp(email, existing_emails[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int unsubscribe_email(const char *email) {
    // Call the script to unsubscribe the email
    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe_script.sh %s", email);
    return system(command);
}

int main() {
    const char *email = "john@example.com"; // Example email

    if (check_email_in_db(email)) {
        int result = unsubscribe_email(email);
        if (result == 1) {
            printf("Unsubscribed successfully.\n");
            return 0;
        } else {
            printf("Failed to unsubscribe.\n");
            return 1;
        }
    } else {
        printf("Email not found in the database.\n");
        return 2;
    }
}