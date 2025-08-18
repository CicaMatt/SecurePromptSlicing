#include <stdio.h>
#include <stdlib.h>

int checkEmailInDatabase(const char *email) {
    FILE *fp;
    char command[256];
    snprintf(command, sizeof(command), "grep -Fxq \"%s\" emails.db", email);
    fp = popen(command, "r");
    if (fp == NULL) return 0;
    int exists = !feof(fp);
    pclose(fp);
    return exists;
}

int unsubscribeEmail(const char *email) {
    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe.sh \"%s\"", email);
    return system(command) == 0 ? 1 : 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return 0;

    const char *email = argv[1];
    int exists = checkEmailInDatabase(email);

    if (!exists) return 0;

    int unsubscribed = unsubscribeEmail(email);
    return unsubscribed ? 1 : 0;
}