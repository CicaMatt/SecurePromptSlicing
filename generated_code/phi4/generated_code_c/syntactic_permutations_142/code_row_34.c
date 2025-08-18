#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database connection using a simple array for demonstration purposes.
#define MAX_EMAILS 100
char emails[MAX_EMAILS][256] = {
    "user1@example.com",
    "user2@example.com",
    "unsubscribe_test@example.com"
};
int email_count = 3;

// Function to simulate connecting to the database and checking if an email exists.
int is_email_in_database(const char *email) {
    for (int i = 0; i < email_count; ++i) {
        if (strcmp(emails[i], email) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to simulate removing an email from the database.
void remove_email_from_database(const char *email) {
    for (int i = 0; i < email_count; ++i) {
        if (strcmp(emails[i], email) == 0) {
            // Shift emails down
            memmove(&emails[i], &emails[i + 1], sizeof(char*) * (email_count - i - 1));
            --email_count;
            printf("Email %s successfully unsubscribed.\n", email);
            return;
        }
    }
}

// Unsubscribe function as specified.
void unsubscribe(const char *email) {
    if (is_email_in_database(email)) {
        remove_email_from_database(email);
    } else {
        printf("The email address %s is not in the database.\n", email);
    }
}

int main() {
    char email_input[256];

    // Simulate user input
    printf("Enter your email address to unsubscribe: ");
    if (fgets(email_input, sizeof(email_input), stdin) != NULL) {
        size_t len = strlen(email_input);
        if (len > 0 && email_input[len - 1] == '\n') {
            email_input[len - 1] = '\0'; // Remove trailing newline
        }

        unsubscribe(email_input);
    } else {
        fprintf(stderr, "Error reading input.\n");
    }

    return 0;
}