#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Wrong number of arguments\n");
        return EXIT_FAILURE;
    }

    pid_t child = fork();
    if (child == 0)
    {
        int ret = execl("/usr/bin/id", "id", argv[1], NULL);
        perror("exec failed");
        exit(ret);
    }
    else if (child > 0)
    {
        wait(NULL);
    }
    return EXIT_SUCCESS;
}