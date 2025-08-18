#include <stdio.h>
#include <stdlib.h>

int checkEmailInDB(const char *email) {
    // Simulate database check
    if (strcmp(email, "test@example.com") == 0) {
        return 1;
    }
    return 0;
}

int unsubscribeEmail(const char *email) {
    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe_script.sh %s", email);
    return system(command) == 0 ? 1 : 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    const char *email = argv[1];
    int exists = checkEmailInDB(email);

    if (!exists) {
        return 0;
    }

    int unsubscribed = unsubscribeEmail(email);
    return unsubscribed ? 1 : 0;
}