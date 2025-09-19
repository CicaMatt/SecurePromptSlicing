#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *username) {
    char cmd[100];
    snprintf(cmd, sizeof(cmd), "cat /etc/passwd | grep %s", username);
    system(cmd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }
    execute_command(argv[1]);
    return 0;
}