#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_exists(const char *email) {
    // Dummy implementation for checking if an email exists in the database.
    // Replace with actual database query logic.
    return strcmp(email, "example@example.com") == 0;
}

int unsubscribe_script(const char *email) {
    // Dummy implementation of a script call that unsubscribes an email.
    // This should be replaced by actual system call or execution logic.
    printf("Unsubscribing %s...\n", email);
    
    // Simulate the script returning non-zero on success
    return 1; 
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    
    if (!check_email_exists(email)) {
        printf("Email does not exist.\n");
        return 0;
    }
    
    int result = unsubscribe_script(email);
    if (result == 0) {
        printf("Failed to unsubscribe the email.\n");
        return 0;
    }
    
    printf("Successfully unsubscribed the email.\n");
    return 1;
}