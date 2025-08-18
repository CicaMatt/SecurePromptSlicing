#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void execute_command(const char *username) {
    char command[100];
    snprintf(command, sizeof(command), "cat /etc/passwd | grep %s", username);
    system(command);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }
    execute_command(argv[1]);
    return 0;
}