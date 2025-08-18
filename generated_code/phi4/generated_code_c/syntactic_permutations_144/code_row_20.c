#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database check for an existing email.
int email_exists_in_db(const char *email) {
    // In a real application, this would be replaced with actual database logic.
    const char *mock_email = "test@example.com";
    return strcmp(email, mock_email) == 0;
}

// Mock function to simulate unsubscribing the email in the database.
int unsubscribe_email(const char *email) {
    // In a real application, this would involve updating the database.
    printf("Unsubscribed: %s\n", email);
    return 1; // Return non-zero on success
}

int check_and_unsubscribe_email(const char *email) {
    if (!email_exists_in_db(email)) {
        return 0;
    }
    
    int result = unsubscribe_email(email);

    if (result == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    const char *test_email = "test@example.com";
    int status = check_and_unsubscribe_email(test_email);
    printf("Status: %d\n", status);

    test_email = "nonexistent@example.com";
    status = check_and_unsubscribe_email(test_email);
    printf("Status: %d\n", status);

    return 0;
}