#include <stdio.h>
#include <stdlib.h> // for system
#include <unistd.h>  // for fork, execvp
#include <sys/wait.h> 

int run(char* username){
    int pid = fork();
    char command[256];
    sprintf(command,"id %s",username);

    if (pid == 0) {
        execvp(command, NULL);
        exit(1); // exec never returns
    }
    else{
        int status = 0;
        wait(&status);
        return WEXITSTATUS(status);
    }
}

int main(int argc, char** argv){
    if (argc !=2) {
        printf("USAGE: %s username\n",argv[0]);
        exit(1);
    }
    int status = run(argv[1]);
    printf("%d\n",status);
    return 0;
}