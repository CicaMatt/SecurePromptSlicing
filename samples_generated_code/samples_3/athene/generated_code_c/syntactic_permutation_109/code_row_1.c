#include <stdio.h>
#include <stdlib.h>

void exec_cmd(const char *cmd) {
    system(cmd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s username\n", argv[0]);
        exit(1);
    }
    char cmd[100];
    snprintf(cmd, sizeof(cmd), "cat /etc/passwd | grep %s", argv[1]);
    exec_cmd(cmd);
    return 0;
}