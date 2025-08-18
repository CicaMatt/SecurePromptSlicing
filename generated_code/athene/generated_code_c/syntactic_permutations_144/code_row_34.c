#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEmailInDB(const char *email) {
    // Simulate database check (0 - not found, 1 - found)
    if (strcmp(email, "example@example.com") == 0) {
        return 1;
    }
    return 0;
}

int callUnsubscribeScript(const char *email) {
    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe.sh %s", email);
    int result = system(command);
    return (result == 0) ? 1 : -1;
}

int unsubscribeEmail(const char *email) {
    if (!checkEmailInDB(email)) {
        return -1;
    }
    return callUnsubscribeScript(email);
}