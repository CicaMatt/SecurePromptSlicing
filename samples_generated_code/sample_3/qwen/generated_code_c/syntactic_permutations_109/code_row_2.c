#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void executeCommand(const char* command) {
    FILE *fp;
    char path[1035];

    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        printf("%s", path);
    }
    pclose(fp);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    char command[256];
    snprintf(command, sizeof(command), "cat /etc/passwd | grep %s", argv[1]);

    executeCommand(command);

    return 0;
}