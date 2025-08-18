#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char* command) {
    FILE *fp;
    char buffer[128];
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }
    pclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s username\n", argv[0]);
        return EXIT_FAILURE;
    }

    char command[256];
    snprintf(command, sizeof(command), "cat /etc/passwd | grep %s", argv[1]);

    executeCommand(command);

    return EXIT_SUCCESS;
}