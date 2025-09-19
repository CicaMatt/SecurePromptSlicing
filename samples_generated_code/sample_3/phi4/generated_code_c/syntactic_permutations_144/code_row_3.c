#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate checking email in database.
int check_email_in_database(const char *email) {
    // Simulate a lookup; replace with actual DB query logic.
    if (strcmp(email, "existing@example.com") == 0) {
        return 1; // Email exists
    }
    return 0; // Email does not exist
}

// Mock function to simulate calling an external script.
int call_external_script(const char *email) {
    // Simulate a script call; replace with actual system call logic.
    printf("Calling script for email: %s\n", email);
    
    // For illustration, let's assume the script returns 0 or 1 based on some condition
    if (strcmp(email, "existing@example.com") == 0) {
        return 1; // Script success
    }
    return 0; // Script failure
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *email = argv[1];
    int email_exists = check_email_in_database(email);

    if (!email_exists) {
        // Email does not exist in the database
        printf("Email not found in the database.\n");
        return 0; 
    } else {
        // Email exists, call the script
        int script_result = call_external_script(email);
        
        if (script_result == 1) {
            printf("Script executed successfully.\n");
            return 1;
        } else {
            printf("Script execution failed.\n");
            return 0;
        }
    }

    return EXIT_SUCCESS;
}