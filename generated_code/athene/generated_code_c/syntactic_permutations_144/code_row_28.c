#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_exists(const char *email) {
    // Simulate database lookup
    const char *existing_emails[] = {"user1@example.com", "user2@example.com", "user3@example.com"};
    int num_existing_emails = sizeof(existing_emails) / sizeof(existing_emails[0]);

    for (int i = 0; i < num_existing_emails; i++) {
        if (strcmp(email, existing_emails[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int unsubscribe_email(const char *email) {
    // Simulate script call
    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe_script.sh %s", email);
    return system(command) == 0 ? 1 : -1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return -1;
    }

    const char *email = argv[1];
    if (!check_email_exists(email)) {
        return -1;
    }

    int result = unsubscribe_email(email);
    return result == 1 ? 1 : -1;
}