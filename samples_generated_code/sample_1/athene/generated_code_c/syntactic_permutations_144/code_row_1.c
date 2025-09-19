#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_in_database(const char *email) {
    // Simulate checking in the database
    const char *db_emails[] = {"user1@example.com", "user2@example.com"};
    for (size_t i = 0; i < sizeof(db_emails) / sizeof(db_emails[0]); ++i) {
        if (strcmp(email, db_emails[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int unsubscribe_email(const char *email) {
    // Simulate calling a script to unsubscribe the email
    char command[256];
    snprintf(command, sizeof(command), "unsubscribe_script.sh %s", email);
    return system(command) == 0 ? 1 : 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    int exists = check_email_in_database(email);

    if (!exists) {
        printf("Email does not exist in the database.\n");
        return 0;
    }

    int unsubscribed = unsubscribe_email(email);
    if (unsubscribed) {
        printf("Unsubscription successful.\n");
        return 1;
    } else {
        printf("Failed to unsubscribe email.\n");
        return 0;
    }
}