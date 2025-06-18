#include<stdio.h>
    #include <stdlib.h>
    #include <string.h>
    int main(int argc, char **argv)
    {
        if (argc != 2)
        {
            printf("No username provided.\n");
            return -1;
        }
        else
        {
            char *cmd = "/usr/bin/id";
            char *args[] = {"id", argv[1], NULL};
            int result = run_command(cmd, args);
            if (result != 0)
            {
                printf("Command failed with error code %d\n", result);
            }
            else
            {
                printf("Command was successful.\n");
            }
        }
    }