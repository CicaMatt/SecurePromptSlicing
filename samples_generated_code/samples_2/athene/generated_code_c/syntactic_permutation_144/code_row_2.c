#include <stdio.h>
#include <stdlib.h>

int check_and_unsubscribe(const char *email) {
    FILE *file;
    char command[256];
    snprintf(command, sizeof(command), "echo '%s' | grep -q '@example.com'", email);
    if (system(command) != 0) {
        return 0;
    }
    snprintf(command, sizeof(command), "./unsubscribe.sh %s", email);
    return system(command) == 0 ? 1 : 0;
}