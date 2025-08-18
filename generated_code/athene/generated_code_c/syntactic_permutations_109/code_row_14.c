#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        exit(1);
    }

    char command[100];
    snprintf(command, sizeof(command), "cat /etc/passwd | grep %s", argv[1]);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen");
        exit(1);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    pclose(fp);

    return 0;
}