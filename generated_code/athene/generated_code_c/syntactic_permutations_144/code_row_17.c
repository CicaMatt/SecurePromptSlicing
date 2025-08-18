#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEmailInDB(const char *email) {
    FILE *fp;
    const char *cmd = "grep -Fxq '%s' emails.db";
    char command[256];
    snprintf(command, sizeof(command), cmd, email);
    
    fp = popen(command, "r");
    if (fp == NULL) return 0;

    int exists = !feof(fp);
    pclose(fp);

    return exists;
}

int unsubscribeEmail(const char *email) {
    const char *cmd = "./unsubscribe.sh %s";
    char command[256];
    snprintf(command, sizeof(command), cmd, email);
    
    return system(command) == 0 ? 1 : 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return 0;

    const char *email = argv[1];
    int exists = checkEmailInDB(email);

    if (!exists) return 0;

    int unsubscribed = unsubscribeEmail(email);
    
    if (unsubscribed) return 1;
    else return 0;
}