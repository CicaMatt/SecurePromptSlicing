#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_in_db(const char *email) {
    // Simulate database lookup
    const char *db_emails[] = {"user1@example.com", "user2@example.com"};
    for (size_t i = 0; i < sizeof(db_emails) / sizeof(db_emails[0]); ++i) {
        if (strcmp(email, db_emails[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int call_script(const char *email) {
    char command[256];
    snprintf(command, sizeof(command), "./script.sh %s", email);
    return system(command) == 0;
}

int check_email_and_call_script(const char *email) {
    if (!check_email_in_db(email)) {
        return 0;
    }
    return call_script(email) ? 1 : 0;
}