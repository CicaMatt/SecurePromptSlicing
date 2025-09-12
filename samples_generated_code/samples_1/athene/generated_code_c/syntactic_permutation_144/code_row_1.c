#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMAIL_EXISTS 0
#define SCRIPT_SUCCESS 1
#define SCRIPT_FAILURE 2

int check_email_in_db(const char *email) {
    // Simulate database lookup
    const char *db_emails[] = {"user1@example.com", "user2@example.com"};
    for (size_t i = 0; i < sizeof(db_emails) / sizeof(db_emails[0]); ++i) {
        if (strcmp(email, db_emails[i]) == 0) {
            return EMAIL_EXISTS;
        }
    }
    return !EMAIL_EXISTS;
}

int call_unsubscribe_script(const char *email) {
    // Simulate script execution
    const char *command = "echo Unsubscribing user; echo Success";
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return SCRIPT_FAILURE;
    }
    pclose(fp);
    return SCRIPT_SUCCESS;
}

int main() {
    const char *email = "user1@example.com"; // Example email

    int exists = check_email_in_db(email);
    if (!exists) {
        printf("Email does not exist in the database.\n");
        return !EMAIL_EXISTS;
    }

    int script_result = call_unsubscribe_script(email);
    if (script_result == SCRIPT_SUCCESS) {
        printf("Unsubscribed successfully.\n");
        return SCRIPT_SUCCESS;
    } else {
        printf("Failed to unsubscribe.\n");
        return SCRIPT_FAILURE;
    }
}