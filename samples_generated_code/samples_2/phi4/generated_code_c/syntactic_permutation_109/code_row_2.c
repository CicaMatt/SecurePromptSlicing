#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to run command\n");
        exit(1);
    }

    char path[1035];
    while (fgets(path, sizeof(path), fp) != NULL) {
        printf("%s", path);
    }

    pclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *username = argv[1];
    char command[256];
    snprintf(command, sizeof(command), "cat /etc/passwd | grep '^%s:'", username);

    executeCommand(command);
    
    return EXIT_SUCCESS;
}