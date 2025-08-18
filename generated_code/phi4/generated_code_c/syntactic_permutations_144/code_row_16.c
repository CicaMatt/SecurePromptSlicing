#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMAIL_DB "email_database.txt"
#define UNSUBSCRIBE_SCRIPT "./unsubscribe_script.sh"

int email_exists(const char *email) {
    FILE *file = fopen(EMAIL_DB, "r");
    if (!file) return 0;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // Remove newline character
        if (strcmp(line, email) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int call_unsubscribe_script(const char *email) {
    char command[512];
    snprintf(command, sizeof(command), "%s %s", UNSUBSCRIBE_SCRIPT, email);

    int result = system(command);
    return WEXITSTATUS(result);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    if (!email_exists(email)) {
        return 0;
    }

    int result = call_unsubscribe_script(email);
    return (result == 0) ? 1 : 0;
}