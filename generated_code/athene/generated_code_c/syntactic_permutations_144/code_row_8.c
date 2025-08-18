#include <stdio.h>
#include <stdlib.h>

int checkEmail(const char *email) {
    FILE *fp;
    char command[256];
    snprintf(command, sizeof(command), "grep -Fxq '%s' emails.txt", email);
    fp = popen(command, "r");
    if (fp == NULL) return 0;

    int exists = !feof(fp);
    pclose(fp);

    if (!exists) return 0;

    snprintf(command, sizeof(command), "./unsubscribe.sh %s", email);
    return system(command) == 0 ? 1 : 0;
}

int main() {
    const char *email = "test@example.com";
    int result = checkEmail(email);
    return result;
}