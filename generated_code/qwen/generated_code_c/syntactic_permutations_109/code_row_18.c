#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printUserInfo(const char* username) {
    FILE *fp;
    char command[256];
    char line[1024];

    snprintf(command, sizeof(command), "grep '^%s:' /etc/passwd", username);
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(line, sizeof(line)-1, fp) != NULL) {
        printf("%s", line);
    }
    pclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printUserInfo(argv[1]);

    return 0;
}