#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEmailInDatabase(const char *email) {
    FILE *fp;
    char path[1035];
    char *command = "grep -Fxq ";
    char *dbFile = "database.txt";
    int exists;

    // Construct the command to check if email exists in database
    sprintf(path, "%s \"%s\" %s", command, email, dbFile);
    fp = popen(path, "r");

    if (fp == NULL) {
        return 0;
    }

    exists = fgetc(fp) != EOF;

    pclose(fp);

    return exists ? 1 : 0;
}

int callUnsubscribeScript(const char *email) {
    char command[256];
    sprintf(command, "./unsubscribe.sh \"%s\"", email);
    return system(command) == 0 ? 1 : 0;
}

int main() {
    const char *email = "example@example.com";
    if (checkEmailInDatabase(email)) {
        if (callUnsubscribeScript(email)) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}