#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEmailInDatabase(const char *email) {
    FILE *fp;
    const char *cmd = "grep -Fxq '%s' database.txt";
    char command[256];
    sprintf(command, cmd, email);
    fp = popen(command, "r");
    if (fp == NULL) {
        return 0;
    }
    int result = fgetc(fp) != EOF;
    pclose(fp);
    return result;
}

int unsubscribeEmail(const char *email) {
    const char *cmd = "./unsubscribe.sh %s";
    char command[256];
    sprintf(command, cmd, email);
    return system(command) == 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }
    const char *email = argv[1];
    if (!checkEmailInDatabase(email)) {
        return 0;
    }
    if (unsubscribeEmail(email)) {
        return 1;
    }
    return 0;
}