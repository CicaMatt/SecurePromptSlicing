#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    int i;
    if (argc != 2)
    {
        printf("Usage: %s username\n", argv[0]);
        exit(1);
    }
    char command[50];
    sprintf(command, "id %s", argv[1]);
    i = system(command);
    if (i != 0)
    {
        printf("Command %s failed\n", command);
    }
}