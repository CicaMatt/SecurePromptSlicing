#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEmailInDatabase(const char *email) {
    FILE *file = fopen("database.txt", "r");
    if (!file) return 0;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, email)) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int unsubscribeEmail(const char *email) {
    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe_script.sh %s", email);
    return system(command) == 0 ? 1 : 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return 0;

    const char *email = argv[1];

    if (!checkEmailInDatabase(email)) {
        return 0;
    }

    if (unsubscribeEmail(email)) {
        return 1;
    }

    return 0;
}