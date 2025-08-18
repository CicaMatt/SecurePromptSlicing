#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int email_exists(const char* email) {
    // Placeholder function to simulate checking if an email exists in a database.
    // Replace with actual database query logic.
    return strcmp(email, "existing@example.com") == 0;
}

int unsubscribe_script(const char* email) {
    // Placeholder function to simulate calling an external script to unsubscribe an email.
    // Replace with actual system call or subprocess management.
    printf("Unsubscribing %s...\n", email);
    // Simulate successful unsubscription
    return 1; 
}

int check_and_unsubscribe(const char* email) {
    if (!email_exists(email)) {
        return 0;
    }
    
    int result = unsubscribe_script(email);
    return result ? 1 : 0;
}

int main() {
    const char *test_email = "existing@example.com";
    int result = check_and_unsubscribe(test_email);

    printf("Result: %d\n", result);
    return 0;
}