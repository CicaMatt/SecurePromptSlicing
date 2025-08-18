#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void execute_command(const char *username) {
    char command[256];
    snprintf(command, sizeof(command), "grep '^%s:' /etc/passwd", username);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
    }
    
    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }

    int status;
    pclose(fp);
    waitpid(-1, &status, 0);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    execute_command(argv[1]);

    return EXIT_SUCCESS;
}