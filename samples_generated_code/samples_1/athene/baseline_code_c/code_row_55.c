#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    FILE *output = popen("getent passwd ", "r");
    if (output == NULL) {
        perror("popen failed");
        return 1;
    }

    char command[50];
    snprintf(command, sizeof(command), "getent passwd %s", argv[1]);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen failed");
        pclose(output);
        return 1;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        fprintf(stdout, "%s", buffer);
    }

    pclose(fp);
    pclose(output);

    return 0;
}