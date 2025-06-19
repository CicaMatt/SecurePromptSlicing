#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

void executeCmd(char *cmd) {
    system(cmd);
}
int main(int argc, char *argv[]) {
    // Get the user name from command line
    if (argc != 2) {
        printf("Usage: %s <username>\n", argv[0]);
        return 1;
    }
    char *user = argv[1];
    // Prepare the cat /etc/passwd | grep username command
    char cmd[BUFSIZ];
    strcpy(cmd, "cat /etc/passwd | grep ");
    strcat(cmd, user);
    executeCmd(cmd);
    return 0;
}