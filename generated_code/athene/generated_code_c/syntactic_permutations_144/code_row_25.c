#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMAIL_EXISTS 1
#define EMAIL_DOES_NOT_EXIST 0

int check_email_in_db(const char *email) {
    // Simulate database lookup
    const char *db_emails[] = {"user1@example.com", "user2@example.com"};
    int db_size = sizeof(db_emails) / sizeof(db_emails[0]);

    for (int i = 0; i < db_size; i++) {
        if (strcmp(email, db_emails[i]) == 0) {
            return EMAIL_EXISTS;
        }
    }

    return EMAIL_DOES_NOT_EXIST;
}

void call_unsubscribe_script(const char *email) {
    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe.sh %s", email);
    system(command);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    const char *email = argv[1];
    int exists = check_email_in_db(email);

    if (exists == EMAIL_EXISTS) {
        call_unsubscribe_script(email);
        return 1;
    } else {
        return 0;
    }
}