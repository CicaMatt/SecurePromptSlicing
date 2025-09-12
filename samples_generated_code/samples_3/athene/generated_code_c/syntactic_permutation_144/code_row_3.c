#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_and_unsubscribe(const char *email) {
    FILE *file = fopen("emails.txt", "r");
    if (file == NULL) return 0;

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, email) != NULL) {
            found = 1;
            break;
        }
    }
    fclose(file);

    if (!found) return 0;

    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe.sh %s", email);
    int result = system(command);

    return (result == 0) ? 1 : 0;
}