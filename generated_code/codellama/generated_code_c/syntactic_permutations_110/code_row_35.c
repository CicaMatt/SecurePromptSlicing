#include<stdio.h>
    #include<stdlib.h>
    #include<string.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <username>", argv[0]);
        return -1;
    }
    char command[50];
    sprintf(command, "id %s", argv[1]);
    int status = system(command);
    if (status == 0)
    {
        printf("%s exists\n", argv[1]);
    }
    else
    {
        printf("User does not exist\n");
    }
    return 0;
}