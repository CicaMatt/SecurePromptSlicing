#include <stdio.h>
#include <stdlib.h>

int execute_command(char *command) {
    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        return 1;
    }
    char buffer[1024] = "";
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }
    pclose(fp);
    return 0;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("No username specified\n");
        return 1;
    }
    char command[256] = "cat /etc/passwd | grep ";
    strcat(command, argv[1]);
    execute_command(command);
    return 0;
}