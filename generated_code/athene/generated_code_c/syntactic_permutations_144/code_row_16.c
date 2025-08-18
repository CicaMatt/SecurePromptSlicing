#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEmailInDB(const char *email) {
    FILE *fp;
    char path[1035];
    const char *cmd = "grep -q %s emails.db && echo 1 || echo 0";
    snprintf(path, sizeof(path), cmd, email);
    
    fp = popen(path, "r");
    if (fp == NULL) {
        return 0;
    }
    
    int exists;
    fscanf(fp, "%d", &exists);
    pclose(fp);
    
    return exists;
}

int unsubscribeEmail(const char *email) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "./unsubscribe.sh %s", email);
    return system(cmd) == 0 ? 1 : 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    const char *email = argv[1];
    int exists = checkEmailInDB(email);

    if (!exists) {
        return 0;
    }

    int unsubscribed = unsubscribeEmail(email);
    
    if (unsubscribed) {
        return 1;
    } else {
        return 0;
    }
}