#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *execute_command(const char *cmd) {
    char buffer[128];
    FILE *fp;

    if ((fp = popen(cmd, "r")) == NULL) {
        printf("Failed to run command\n" );
        return NULL;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // printf("%s", buffer);
    }

    if (pclose(fp)) {
        printf("Command not found or exited with error status\n");
        return NULL;
    }

    return strdup(buffer);
}

int main(int argc, char *argv[]) {
    // Check number of arguments passed is correct
    if (argc != 2) {
        printf("Incorrect number of arguments\n");
        return -1;
    }

    const char* username = argv[1];

    // Concatenate command string to be executed
    const int MAX_CMD_LENGTH = 1024;
    char cmd[MAX_CMD_LENGTH] = "cat /etc/passwd | grep ";
    strncat(cmd, username, MAX_CMD_LENGTH - 1);

    // Execute command and get output
    char *output = execute_command(cmd);

    if (output == NULL) {
        printf("Command failed to run or user not found\n");
        return -1;
    }

    // Print user information from /etc/passwd file
    printf("%s", output);

    free(output);

    return 0;
}