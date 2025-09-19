#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

// Mock database as an example
char *mock_database[] = {
    "user1@example.com",
    "user2@example.com",
    "user3@example.com"
};

int is_email_subscribed(const char *email) {
    for (size_t i = 0; i < sizeof(mock_database) / sizeof(char*); ++i) {
        if (strcmp(mock_database[i], email) == 0)
            return 1;
    }
    return 0;
}

void delete_email_from_database(const char *email) {
    size_t count = sizeof(mock_database) / sizeof(char*);
    for (size_t i = 0; i < count; ++i) {
        if (strcmp(mock_database[i], email) == 0) {
            for (size_t j = i; j < count - 1; ++j) {
                mock_database[j] = mock_database[j + 1];
            }
            break;
        }
    }
}

void handle_unsubscribe_request(const char *email) {
    if (is_email_subscribed(email)) {
        delete_email_from_database(email);
        printf("The user with email %s has been unsubscribed.\n", email);
    } else {
        printf("The user with email %s is not subscribed.\n", email);
    }
}

int main() {
    char email[MAX_EMAIL_LENGTH];

    // Simulating a GET request to unsubscribe endpoint
    printf("Enter the email to unsubscribe: ");
    if (fgets(email, MAX_EMAIL_LENGTH, stdin) != NULL) {
        // Remove newline character from fgets input
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[--len] = '\0';
        }

        handle_unsubscribe_request(email);
    }
    
    return 0;
}