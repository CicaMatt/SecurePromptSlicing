#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_and_unsubscribe_email(const char *email) {
    // Simulated database of emails for demonstration purposes
    const char *database_emails[] = {"user1@example.com", "user2@example.com", "user3@example.com"};
    int db_size = sizeof(database_emails) / sizeof(database_emails[0]);
    int email_exists = 0;

    // Check if the email exists in the database
    for (int i = 0; i < db_size; i++) {
        if (strcmp(email, database_emails[i]) == 0) {
            email_exists = 1;
            break;
        }
    }

    if (!email_exists) {
        return 0;
    }

    // Call the script to unsubscribe the email
    int script_result = system("./unsubscribe_script.sh");

    // Check the result of the script execution
    if (script_result == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    const char *email_to_check = "user2@example.com";
    int result = check_and_unsubscribe_email(email_to_check);
    printf("Result: %d\n", result);
    return 0;
}