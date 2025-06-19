#include <stdlib.h>  // for system
#include <stdio.h>   // for printf

int main(int argc, char** argv)
{
    int exit_status;

    if (argc != 2)
    {
        printf("Please provide a username\n");
        return 1;
    }
    
    exit_status = system(argv[1]);
    
    if (exit_status == 0)
    {
        printf("Command successful. Exit status: %d\n", exit_status);
    }
    else
    {
        printf("Command failed. Exit status: %d\n", exit_status);
    }
    
    return 0;
}