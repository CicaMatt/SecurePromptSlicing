#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>

    int main(int argc, char *argv[]) {
        char *target = getenv("TARGET");
        if (target == NULL) {
            printf("Environment variable TARGET not set\n");
            return -1;
        }

        int match = regexec(&regex, target, 0, NULL, 0);
        if (match != 0) {
            printf("Target does not match example.com\n");
            return -2;
        }

        char *cmd[] = {"/usr/bin/curl", "-L", "--silent", target};
        execvp(cmd[0], cmd);
    }