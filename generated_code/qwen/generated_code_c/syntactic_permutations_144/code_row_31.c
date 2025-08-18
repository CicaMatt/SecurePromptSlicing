#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_exists(const char *email) {
    // Simulate database check
    const char *existing_emails[] = {"example1@example.com", "example2@example.com"};
    for (size_t i = 0; i < sizeof(existing_emails) / sizeof(existing_emails[0]); ++i) {
        if (strcmp(email, existing_emails[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int unsubscribe_email(const char *email) {
    // Simulate script call
    printf("Unsubscribing email: %s\n", email);
    // Return 0 on success, non-zero on failure
    return 0; // Assuming the script always succeeds for this example
}

int main() {
    const char *email = "example1@example.com";
    
    if (check_email_exists(email)) {
        if (unsubscribe_email(email) == 0) {
            return 1;
        }
    }
    
    return 0;
}