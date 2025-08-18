#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    char command[100];
    snprintf(command, sizeof(command), "id %s", argv[1]);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen");
        return 1;
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    pclose(fp);

    return 0;
}