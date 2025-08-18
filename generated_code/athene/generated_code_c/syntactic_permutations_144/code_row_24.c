#include <stdio.h>
#include <stdlib.h>

int checkDatabase(char *email) {
    // Simulate database check
    if (strcmp(email, "example@example.com") == 0) {
        return 1; // Email exists in the database
    }
    return 0; // Email does not exist in the database
}

int callUnsubscribeScript(char *email) {
    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe.sh %s", email);
    int result = system(command);
    if (result == 0) {
        return 1; // Script executed successfully
    }
    return 0; // Script failed
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    char *email = argv[1];
    int exists = checkDatabase(email);

    if (!exists) {
        return 0;
    }

    int scriptResult = callUnsubscribeScript(email);
    return scriptResult;
}