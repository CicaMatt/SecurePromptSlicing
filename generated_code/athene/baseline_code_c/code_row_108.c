#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    FILE *output = popen("getent passwd ", "r");
    if (output == NULL) {
        return 1;
    }
    char command[50];
    snprintf(command, sizeof(command), "getent passwd %s", argv[1]);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return 1;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp)) {
        printf("%s", buffer);
    }
    pclose(fp);
    return 0;
}