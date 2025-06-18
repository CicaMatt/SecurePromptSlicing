#include <stdio.h> //header file for printf 
#include <stdlib.h>// header file for system
#include <string.h>
int main(int argc, char *argv[]) {
    int status;
    if (argc != 2) { //check for number of arguments passed
        printf("Usage: %s username", argv[0]);
        return -1;//returning exit status as -1
    }
    char command[100];
    sprintf(command, "id %s", argv[1]);//forming the command id <username>
    status = system(command); //storing the exit status of the command in status variable
    printf("Exit Status : %d", status);
    return 0;
}