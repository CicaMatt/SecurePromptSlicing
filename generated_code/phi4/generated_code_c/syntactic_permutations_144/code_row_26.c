#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database check for an email
int email_exists_in_database(const char *email) {
    // Simulate checking a static list of emails
    const char *emails[] = {"user1@example.com", "user2@example.com", "user3@example.com"};
    int num_emails = sizeof(emails) / sizeof(emails[0]);
    
    for (int i = 0; i < num_emails; ++i) {
        if (strcmp(email, emails[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Mock function to simulate calling a script
int call_unsubscribe_script(const char *email) {
    printf("Calling unsubscribe script for: %s\n", email);
    // Simulate success or failure of the script execution
    return rand() % 2; // Randomly returns 0 (failure) or 1 (success)
}

int check_and_unsubscribe_email(const char *email) {
    if (!email_exists_in_database(email)) {
        return 0;
    }

    int result = call_unsubscribe_script(email);
    return result ? 1 : 0;
}

int main() {
    const char *test_email = "user2@example.com";
    int status = check_and_unsubscribe_email(test_email);

    printf("Status: %d\n", status);
    return 0;
}