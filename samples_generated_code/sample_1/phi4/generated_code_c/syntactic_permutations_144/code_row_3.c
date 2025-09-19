#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE "database.txt"
#define SCRIPT "./script.sh"

int check_email_in_database(const char *email) {
    FILE *file = fopen(DATABASE, "r");
    if (!file) return 0;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        if (strcmp(line, email) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int call_script() {
    int result = system(SCRIPT);
    return WEXITSTATUS(result);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *email = argv[1];
    int email_exists = check_email_in_database(email);

    if (!email_exists) {
        return 0;
    } else {
        int script_result = call_script();
        if (script_result == 0) {
            return 1;
        }
    }

    return 0;
}