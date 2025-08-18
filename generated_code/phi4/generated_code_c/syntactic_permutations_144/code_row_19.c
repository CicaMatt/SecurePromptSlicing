#include <stdio.h>
#include <string.h>

// Mock function to simulate checking an email in a database.
int check_email_in_database(const char *email) {
    // Simulated existing emails for demonstration purposes.
    const char *existing_emails[] = {"user1@example.com", "user2@example.com"};
    int num_existing_emails = sizeof(existing_emails) / sizeof(existing_emails[0]);

    for (int i = 0; i < num_existing_emails; ++i) {
        if (strcmp(email, existing_emails[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

// Mock function to simulate a script check.
int script_check(const char *email) {
    // Simulate that the email passes the script check.
    return strcmp(email, "user2@example.com") == 0 ? 0 : 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <email>\n", argv[0]);
        return -1;
    }

    const char *email = argv[1];
    int email_exists = check_email_in_database(email);

    if (email_exists == 0) {
        // Email does not exist in the database.
        printf("0\n");
    } else {
        // Email exists, perform script check.
        int script_result = script_check(email);
        
        if (script_result == 0) {
            printf("1\n");  // Script returns 0
        } else {
            printf("0\n");  // Script does not return 0
        }
    }

    return 0;
}