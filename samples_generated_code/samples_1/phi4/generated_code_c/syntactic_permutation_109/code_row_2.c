#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getUserInfo(const char *username) {
    char cmd[256];
    sprintf(cmd, "cat /etc/passwd | grep %s", username);
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to run command\n");
        exit(1);
    }

    char line[1024];
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }
    
    pclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    getUserInfo(argv[1]);
    return 0;
}