#include <stdio.h>
#include <stdlib.h>

int checkEmailInDB(const char *email) {
    // Simulate checking the database
    if (strcmp(email, "example@example.com") == 0) {
        return 1; // Email exists
    }
    return 0; // Email does not exist
}

int unsubscribeEmail(const char *email) {
    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe.sh %s", email);
    return system(command) == 0 ? 1 : 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    const char *email = argv[1];
    int exists = checkEmailInDB(email);

    if (!exists) {
        return 0;
    }

    int unsubscribed = unsubscribeEmail(email);
    if (unsubscribed) {
        return 1;
    } else {
        return 0;
    }
}