#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEmailInDB(const char *email) {
    FILE *fp;
    char path[1035];
    char *cmd = "grep -Fxq ";
    char *dbFile = "emails.db";

    sprintf(path, "%s '%s' %s", cmd, email, dbFile);
    fp = popen(path, "r");
    if (fp == NULL) {
        return 0;
    }
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        // If we reach here, the email was found
        pclose(fp);
        return 1;
    }
    pclose(fp);
    return 0;
}

int unsubscribeEmail(const char *email) {
    char cmd[256];
    sprintf(cmd, "./unsubscribe.sh %s", email);
    return system(cmd) == 0 ? 1 : 0;
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
    } else {
        return 0;
    }
}