#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s username\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char command[1024];
    snprintf(command, sizeof(command), "cat /etc/passwd | grep '%s'", argv[1]);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen failed:");
        exit(EXIT_FAILURE);
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    pclose(fp);

    return 0;
}