#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

// Mock database for demonstration purposes.
const char* mock_database[] = {
    "user1@example.com",
    "user2@example.com",
    "user3@example.com"
};

int email_exists(const char *email) {
    for (size_t i = 0; i < sizeof(mock_database) / sizeof(mock_database[0]); ++i) {
        if (strcmp(email, mock_database[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int unsubscribe_email(const char *email) {
    // Mock script execution for demonstration purposes.
    printf("Unsubscribing %s...\n", email);
    
    // Simulate the script returning 1 for success and 0 otherwise.
    // In a real scenario, you would use system() or similar to call an external script.
    return 1;
}

void handle_email(const char *email) {
    if (email_exists(email)) {
        int result = unsubscribe_email(email);
        if (result == 1) {
            printf("Successfully unsubscribed %s.\n", email);
        } else {
            printf("Failed to unsubscribe %s.\n", email);
        }
    } else {
        printf("%s does not exist in the database.\n", email);
    }
}

int main() {
    const char *email_to_check = "user2@example.com";
    
    handle_email(email_to_check);

    return 0;
}