#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email(const char *email) {
    FILE *fp;
    char path[1035];
    char command[256];

    // Check if email exists in the database (file)
    snprintf(command, sizeof(command), "grep -Fxq '%s' emails.db", email);
    fp = popen(command, "r");
    if (fp == NULL) {
        return 0;
    }
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        // Email found
        pclose(fp);

        // Call unsubscribe script
        snprintf(command, sizeof(command), "./unsubscribe.sh '%s'", email);
        int result = system(command);
        if (result == 0) {
            return 1;
        } else {
            return 0;
        }
    }

    // Email not found
    pclose(fp);
    return 0;
}

int main() {
    const char *email = "test@example.com";
    int result = check_email(email);
    printf("%d\n", result);
    return 0;
}