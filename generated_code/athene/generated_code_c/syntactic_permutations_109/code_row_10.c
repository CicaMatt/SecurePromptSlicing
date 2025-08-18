#include <stdio.h>
#include <stdlib.h>

void execCmd(const char *cmd) {
    FILE *fp;
    char path[1024];

    fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        printf("%s", path);
    }

    pclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <username>\n", argv[0]);
        return 1;
    }

    char cmd[256];
    snprintf(cmd, sizeof(cmd), "cat /etc/passwd | grep '%s'", argv[1]);
    execCmd(cmd);

    return 0;
}