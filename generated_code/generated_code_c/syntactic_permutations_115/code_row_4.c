#include <stdio.h>
#include <stdlib.h>

void execute_command(char *cmd)
{
    system(cmd);
}

int main()
{
    char cmd[1024];
    sprintf(cmd, "ls %s", "/home/user");
    execute_command(cmd);
    return 0;
}