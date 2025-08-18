#include <stdio.h>
#include <stdlib.h>

int checkEmailInDB(const char *email) {
    FILE *fp;
    char command[256];
    snprintf(command, sizeof(command), "grep -Fxq '%s' emails.db", email);
    fp = popen(command, "r");
    if (fp == NULL) return 0;
    int result = fgetc(fp) == EOF;
    pclose(fp);
    return !result; // Invert to match the logic: found -> 1, not found -> 0
}

int unsubscribeEmail(const char *email) {
    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe_script.sh %s", email);
    return system(command) == 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }
    const char *email = argv[1];
    if (!checkEmailInDB(email)) {
        return 0;
    }
    if (unsubscribeEmail(email)) {
        return 1;
    }
    return 0;
}