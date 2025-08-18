#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkAndUnsubscribe(const char *email) {
    const char *check_script = "check_email.sh";
    const char *unsubscribe_script = "unsubscribe_email.sh";

    char cmd[256];
    snprintf(cmd, sizeof(cmd), "%s %s", check_script, email);
    FILE *fp;
    fp = popen(cmd, "r");
    if (fp == NULL) {
        return 0;
    }

    char result[10];
    fgets(result, sizeof(result), fp);
    pclose(fp);

    if (strcmp(result, "1\n") != 0) {
        return 0;
    }

    snprintf(cmd, sizeof(cmd), "%s %s", unsubscribe_script, email);
    int status = system(cmd);

    if (status == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    const char *email = "test@example.com";
    int result = checkAndUnsubscribe(email);
    printf("%d\n", result);
    return 0;
}