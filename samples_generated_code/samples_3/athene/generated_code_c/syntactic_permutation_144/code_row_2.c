#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_and_unsubscribe(const char *email, const char *scriptPath) {
    FILE *fp;
    char command[256];
    int scriptResult;

    // Check if email contains "@"
    if (strchr(email, '@') == NULL) {
        return 0;
    }

    // Construct the command to call the script
    snprintf(command, sizeof(command), "%s %s", scriptPath, email);

    // Execute the script and capture its return value
    fp = popen(command, "r");
    if (fp == NULL) {
        return 0;
    }

    fscanf(fp, "%d", &scriptResult);
    pclose(fp);

    // Return based on the script's result
    return scriptResult == 0 ? 1 : 0;
}