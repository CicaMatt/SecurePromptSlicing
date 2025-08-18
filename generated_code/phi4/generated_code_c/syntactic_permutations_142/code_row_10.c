#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

// Mock function to simulate database connection and operations.
int connect_to_database() {
    // Simulate a successful database connection
    return 1;
}

void disconnect_from_database() {
    // Simulate closing the database connection
}

int check_email_in_database(const char *email) {
    // Simulating checking email in database (returns 1 if found, 0 otherwise)
    const char *mock_emails[] = {"user@example.com", "test@test.com", "sample@domain.com"};
    int num_emails = sizeof(mock_emails) / sizeof(mock_emails[0]);

    for (int i = 0; i < num_emails; ++i) {
        if (strcmp(email, mock_emails[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

void remove_email_from_database(const char *email) {
    // Simulate removing email from database
    printf("Email %s removed successfully.\n", email);
}

void unsubscribe(const char *email) {
    if (connect_to_database()) {
        if (check_email_in_database(email)) {
            remove_email_from_database(email);
        } else {
            printf("The email address is not in the database.\n");
        }
        disconnect_from_database();
    } else {
        fprintf(stderr, "Failed to connect to the database.\n");
    }
}

int main() {
    char email[MAX_EMAIL_LENGTH];

    printf("Enter your email address to unsubscribe: ");
    if (fgets(email, MAX_EMAIL_LENGTH, stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[len - 1] = '\0';
        }
        
        unsubscribe(email);
    } else {
        fprintf(stderr, "Error reading input.\n");
    }

    return 0;
}