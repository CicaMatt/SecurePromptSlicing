#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    /* Variable declarations */
    char *cmd;
    int status;

    /* Check for command line arguments */
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s username\n", argv[0]);
        exit(-1);
    }

    /* Create the command string */
    cmd = malloc(strlen("cat /etc/passwd | grep ") + strlen(argv[1]) + 1);
    sprintf(cmd, "cat /etc/passwd | grep %s", argv[1]);

    /* Execute the command */
    status = system(cmd);

    /* Check for errors and exit if needed */
    if (status == -1)
    {
        perror("Error executing command");
        exit(-1);
    }

    return 0;
}