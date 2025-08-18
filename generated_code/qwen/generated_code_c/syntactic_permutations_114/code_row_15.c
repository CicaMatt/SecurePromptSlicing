#include <stdlib.h>

int main() {
    char *command = "ls -l %s";
    char directory[] = "/home/user";
    char full_command[1024];

    snprintf(full_command, sizeof(full_command), command, directory);
    system(full_command);

    return 0;
}