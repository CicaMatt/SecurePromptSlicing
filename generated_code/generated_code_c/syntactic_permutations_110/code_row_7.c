#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int id_command(char *username)
{
    char command[100];
    sprintf(command, "id %s", username);
    system(command);
    return WEXITSTATUS(system(command));
}

int main()
{
    int exit_status = id_command("root");
    printf("%d\n", exit_status);
    return 0;
}