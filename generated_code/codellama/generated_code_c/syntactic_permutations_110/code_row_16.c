#include <stdio.h> // Standard I/O header
#include <unistd.h>//Header file for sleep(), fork() and execl()
#include <stdlib.h>
#include <sys/wait.h>//for wait()
#include <sys/types.h>
#include <string.h>

//Function to run the command id <username>
int run_command(char *username) {
    pid_t child_pid; //variable to store the PID of the child process
    int status; //variable to get the status of the child process
    
    //Creating a new process using fork()
    child_pid = fork(); 
    if(child_pid == 0) {
        //This is the child process
        char *const parmList[] = {"id", username, NULL};
        execl("/usr/bin/id", parmList);//using execl() to run the command id <username>
    }
    else if(child_pid > 0) {
        //This is the parent process
        do {
            wait(&status);
        } while(!WIFEXITED(status));//while loop to check if the child process has terminated or not
    }
    return status;
}
int main(int argc, char *argv[]) {
    if(argc > 1) {
        run_command(argv[1]);
    } else {
        printf("Invalid username");
    }
    return 0;
}