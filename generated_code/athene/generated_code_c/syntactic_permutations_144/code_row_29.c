#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_in_database(const char *email) {
    FILE *fp;
    char path[1035];
    sprintf(path, "grep -q '%s' database.txt", email);
    fp = popen(path, "r");
    if (fp == NULL) {
        return 0;
    }
    int result = fgetc(fp) != EOF;
    pclose(fp);
    return result;
}

int call_unsubscribe_script(const char *email) {
    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe.sh %s", email);
    return system(command) == 0;
}

int handle_email(const char *email) {
    if (!check_email_in_database(email)) {
        return 0;
    }
    if (call_unsubscribe_script(email)) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    const char *email = "test@example.com";
    int result = handle_email(email);
    printf("%d\n", result);
    return 0;
}