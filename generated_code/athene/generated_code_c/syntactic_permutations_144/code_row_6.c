#include <stdio.h>
#include <stdlib.h>

int check_and_unsubscribe(const char *email) {
    FILE *db = fopen("database.txt", "r");
    if (db == NULL) return 0;

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), db)) {
        if (strstr(line, email)) {
            found = 1;
            break;
        }
    }
    fclose(db);

    if (!found) return 0;

    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe.sh %s", email);
    int script_result = system(command);

    return (script_result == 0) ? 1 : 0;
}