#include <stdio.h>
#include <stdlib.h>

int check_email_in_database(const char *email) {
    // Dummy implementation for database check
    if (strcmp(email, "test@example.com") == 0) {
        return 1; // Email exists
    }
    return 0; // Email does not exist
}

int unsubscribe_email(const char *email) {
    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe_script.sh %s", email);
    return system(command) == 0 ? 1 : 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    const char *email = argv[1];
    int exists = check_email_in_database(email);

    if (!exists) {
        return 0;
    }

    int unsubscribed = unsubscribe_email(email);
    return unsubscribed ? 1 : 0;
}