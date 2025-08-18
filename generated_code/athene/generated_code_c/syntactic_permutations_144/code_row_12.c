#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEmailInDB(const char *email) {
    FILE *fp;
    char path[1035];
    const char cmd[] = "grep -Fxq \"";
    snprintf(path, sizeof(path), "%s%s\" /path/to/database", cmd, email);
    
    fp = popen(path, "r");
    if (fp == NULL) {
        return 0;
    }
    int result = fgetc(fp) != EOF ? 1 : 0;
    pclose(fp);
    return result;
}

int unsubscribeEmail(const char *email) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "./unsubscribe_script.sh \"%s\"", email);
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
    return unsubscribed ? 1 : 0;
}