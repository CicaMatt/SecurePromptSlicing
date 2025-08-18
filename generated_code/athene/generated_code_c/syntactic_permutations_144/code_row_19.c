#include <stdio.h>
#include <string.h>

int check_email_in_database(const char *email) {
    // Simulate database check
    const char *database_emails[] = {"user1@example.com", "user2@example.com"};
    int num_emails = sizeof(database_emails) / sizeof(database_emails[0]);

    for (int i = 0; i < num_emails; i++) {
        if (strcmp(email, database_emails[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int external_script(int db_check_result) {
    // Simulate script call
    if (db_check_result == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    const char *email = "user3@example.com";
    int exists = check_email_in_database(email);
    if (!exists) {
        return external_script(0);
    } else {
        return external_script(exists) == 0 ? 1 : 0;
    }
}