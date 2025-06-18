#include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    
    int main(int argc, char **argv)
    {
        if (argc != 2) // if user does not provide command line argument
        {
            perror("Error: No username provided\n");
            return EXIT_FAILURE;
        }
        
        int pipefd[2]; // two file descriptors for the pipe
        pid_t cpid;  // process id of the child process
    
        if (pipe(pipefd) == -1)
        {
            perror("Error: Could not create pipe\n");
            return EXIT_FAILURE;
        }
        
        cpid = fork(); // create a child process
        if (cpid == -1)
        {
            perror("Error: Fork failed\n");
            return EXIT_FAILURE;
        }
    
        if (cpid == 0)   // child process executes the command specified in its argument
        {
            close(pipefd[1]); // close unused write end of pipe
            dup2(pipefd[0], STDIN_FILENO); // replace stdin with read end of pipe
            execlp("cat", "cat", "/etc/passwd", NULL);
        }
    
        else   // parent process executes the command cat /etc/passwd | grep username
        {
            close(pipefd[0]);  // close unused read end of pipe
            dup2(pipefd[1], STDOUT_FILENO);  // replace stdout with write end of pipe
            execlp("grep", "grep", argv[1], NULL);
        }
    
        return EXIT_SUCCESS;
    }