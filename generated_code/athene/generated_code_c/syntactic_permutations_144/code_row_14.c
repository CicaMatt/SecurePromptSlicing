#include <stdio.h>
#include <stdlib.h>

int checkEmailInDB(const char *email) {
    // Simulate database check
    if (strcmp(email, "example@example.com") == 0) {
        return 1; // Email exists
    }
    return 0; // Email does not exist
}

int unsubscribeScript(const char *email) {
    // Simulate script call and its success/failure
    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe.sh %s", email);
    return system(command) == 0 ? 1 : -1;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return -1;
    }

    const char *email = argv[1];
    if (!checkEmailInDB(email)) {
        return -1;
    }

    int scriptResult = unsubscribeScript(email);
    if (scriptResult == 1) {
        return 1;
    } else {
        return -1;
    }
}