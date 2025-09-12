#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void execute_command(const char *username) {
    char command[256];
    snprintf(command, sizeof(command), "cat /etc/passwd | grep %s", username);
    FILE *fp = popen(command, "r");
    
    if (fp == NULL) {
        fprintf(stderr, "Failed to run command\n");
        exit(EXIT_FAILURE);
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
        return EXIT_FAILURE;
    }

    execute_command(argv[1]);

    return EXIT_SUCCESS;
}