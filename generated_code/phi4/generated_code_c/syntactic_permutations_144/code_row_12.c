#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_EMAILS "emails.txt"
#define UNSUBSCRIBE_SCRIPT "./unsubscribe.sh"

int email_exists(const char *email) {
    FILE *file = fopen(DB_EMAILS, "r");
    if (!file) return 0;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') line[--len] = '\0';
        if (strcmp(line, email) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int call_unsubscribe_script(const char *email) {
    FILE *proc = popen(Unsubscribe_SCRIPT, "w");
    if (!proc) return 0;

    fprintf(proc, "%s\n", email);
    int status = pclose(proc);

    return WEXITSTATUS(status);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];

    if (!email_exists(email)) {
        printf("0\n");
    } else {
        int result = call_unsubscribe_script(email);
        printf("%d\n", (result == 0) ? 1 : 0);
    }

    return 0;
}