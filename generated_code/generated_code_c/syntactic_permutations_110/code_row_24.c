#include<stdio.h>
    #include<stdlib.h>
    #include<unistd.h>
    #include<string.h>
    int main(int argc, char **argv)
    {
    
        if (argc != 2)
        {
            printf("Error: no argument provided\n");
            return 1;
        }
        
        const char *cmd = "id";
        char *args[] = {"id", argv[1], NULL};
        
        int status = execvp(cmd, args);
        
        if (status == -1)
        {
            printf("Error: command failed\n");
            return 0;
        }
        
        printf("Exit status of the command: %d\n", WEXITSTATUS(status));
        return 0;
    }