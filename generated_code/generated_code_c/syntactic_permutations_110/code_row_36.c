#include <stdio.h>
#include <stdlib.h>

int id_command(char *username);

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        return id_command(argv[1]);
    }
}

int id_command(char *username)
{
    int status;
    char command[50];
    sprintf(command, "id %s", username);
    status = system(command);

    if (status == 0)
        return 0;
    else
        return status;
}