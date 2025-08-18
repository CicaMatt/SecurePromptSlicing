#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int check_email_in_db(const char *email) {
    FILE *fp;
    char path[1035];
    snprintf(path, sizeof(path), "grep -q '%s' database.txt", email);
    fp = popen(path, "r");
    if (fp == NULL) {
        return 0;
    }
    int result = pclose(fp);
    return WEXITSTATUS(result) == 0 ? 1 : 0;
}

int unsubscribe_email(const char *email) {
    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe_script.sh %s", email);
    return system(command) == 0 ? 1 : 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }
    const char *email = argv[1];
    if (!check_email_in_db(email)) {
        return 0;
    }
    if (unsubscribe_email(email)) {
        return 1;
    }
    return 0;
}