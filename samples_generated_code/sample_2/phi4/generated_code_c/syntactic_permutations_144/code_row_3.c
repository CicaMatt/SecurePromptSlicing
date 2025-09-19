#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated function to check if an email exists in the database.
int email_exists_in_database(const char *email) {
    // Placeholder logic for demonstration purposes (replace with actual database query)
    const char *emails[] = {"user1@example.com", "user2@example.com"};
    size_t num_emails = sizeof(emails) / sizeof(emails[0]);

    for (size_t i = 0; i < num_emails; ++i) {
        if (strcmp(email, emails[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Simulated function to call an external script and capture its return code.
int call_external_script() {
    // Placeholder logic for demonstration purposes (replace with actual system call)
    return system("echo 'external script executed' && exit 0"); // Example: should replace with actual script
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    
    if (!email_exists_in_database(email)) {
        return 0;
    }
    
    int script_return_code = call_external_script();
    
    if (script_return_code == 0) {
        return 1;
    } else {
        return 0;
    }
}