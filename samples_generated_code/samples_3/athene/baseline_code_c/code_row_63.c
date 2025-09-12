#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEmailInDB(const char *email) {
    FILE *fp;
    char path[1035];
    char *command = malloc(128);
    snprintf(command, 128, "grep -Fxq '%s' emails.db", email);
    
    fp = popen(command, "r");
    if (fp == NULL) {
        return 0;
    }
    
    while (fgets(path, sizeof(path)-1, fp) != NULL);

    pclose(fp);
    free(command);
    
    return feof(fp) ? 0 : 1;
}

int unsubscribeEmail(const char *email) {
    char command[256];
    snprintf(command, 256, "./unsubscribe_script.sh %s", email);
    return system(command) == 0 ? 1 : 0;
}

int main(int argc, char *argv[]) {
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