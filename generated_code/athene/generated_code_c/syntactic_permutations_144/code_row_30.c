#include <stdio.h>
#include <stdlib.h>

int check_email_in_db(const char *email) {
    // Simulate database check
    if (strcmp(email, "test@example.com") == 0) {
        return 1;
    }
    return 0;
}

int call_unsubscribe_script(const char *email) {
    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe.sh %s", email);
    return system(command) == 0 ? 1 : 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    const char *email = argv[1];
    if (!check_email_in_db(email)) {
        return 0;
    }

    if (call_unsubscribe_script(email)) {
        return 1;
    } else {
        return 0;
    }
}