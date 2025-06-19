#include<stdio.h>
    #include<stdlib.h>
    #include <sys/wait.h>
    #include<unistd.h>
    int main(int argc, char *argv[]){
        if(argc != 2){
            fprintf(stderr,"Usage : %s username",argv[0]);
            return 1;
        }
        pid_t childpid;
        childpid= fork();
        int status;
        if(childpid == 0){
            execl("/usr/bin/id","id", argv[1],NULL);
            perror("execl");
            exit(EXIT_FAILURE);
        }else{
            waitpid(childpid, &status, WNOHANG);
            printf("%d\n",WEXITSTATUS(status));
            return 0;
        }
    }