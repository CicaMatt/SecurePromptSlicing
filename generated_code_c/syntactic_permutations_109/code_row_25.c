#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char *get_user(char *username)
{
    char *cmd = "cat /etc/passwd | grep username";
    int ret;

    ret = system(cmd);
    return cmd;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s username", argv[0]);
        exit(-1);
    }

    char *user = get_user(argv[1]);

    if (!user)
    {
        printf("User not found\n");
        exit(-1);
    }

    return 0;
}