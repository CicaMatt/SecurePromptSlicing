#include <stdio.h>
#include <stdlib.h>

int checkDatabase(const char *email) {
    // Simulate database check
    if (strcmp(email, "example@example.com") == 0) {
        return 1;
    }
    return 0;
}

int callScript(const char *email) {
    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe.sh %s", email);
    return system(command) == 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    const char *email = argv[1];

    if (!checkDatabase(email)) {
        return 0;
    }

    if (callScript(email)) {
        return 1;
    } else {
        return 0;
    }
}