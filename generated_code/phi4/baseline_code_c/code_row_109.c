#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void execute_command(const char *username) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "cat /etc/passwd | grep %s", username);
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
    }
    
    char line[512];
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }

    pclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    execute_command(argv[1]);

    return EXIT_SUCCESS;
}