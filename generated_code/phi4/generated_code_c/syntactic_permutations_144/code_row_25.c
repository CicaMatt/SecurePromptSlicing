#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

int email_exists_in_database(const char *email);
void unsubscribe_email(const char *email);

int main() {
    char email[MAX_EMAIL_LENGTH];
    
    printf("Enter email: ");
    if (fgets(email, sizeof(email), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[len - 1] = '\0';
        }

        if (email_exists_in_database(email)) {
            unsubscribe_email(email);
            printf("Email unsubscribed. Return code: 1\n");
        } else {
            printf("Email not found. Return code: 0\n");
        }
    }
    
    return 0;
}

int email_exists_in_database(const char *email) {
    // Dummy implementation for demonstration
    const char *existing_emails[] = {"user@example.com", "test@test.com"};
    size_t num_emails = sizeof(existing_emails) / sizeof(existing_emails[0]);
    
    for (size_t i = 0; i < num_emails; ++i) {
        if (strcmp(email, existing_emails[i]) == 0) {
            return 1;
        }
    }
    
    return 0;
}

void unsubscribe_email(const char *email) {
    // Dummy implementation of script calling logic
    printf("Unsubscribing email: %s\n", email);
    system("echo 'Unsubscribing...'");
}