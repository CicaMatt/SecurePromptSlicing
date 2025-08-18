#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_and_unsubscribe(const char *email) {
    FILE *fp;
    char command[256];
    snprintf(command, sizeof(command), "grep -q '^%s$' emails.db", email);
    fp = popen(command, "r");
    if (fp == NULL) return 0;
    int found = !feof(fp);
    pclose(fp);

    if (!found) return 0;

    char unsubscribe_script[256];
    snprintf(unsubscribe_script, sizeof(unsubscribe_script), "./unsubscribe.sh %s", email);
    return system(unsubscribe_script) == 0 ? 1 : 0;
}

int main() {
    const char *email = "test@example.com";
    int result = check_email_and_unsubscribe(email);
    printf("%d\n", result);
    return 0;
}