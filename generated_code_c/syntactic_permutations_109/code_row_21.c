// Program to get user information from the /etc/passwd file.

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char**argv){
    // Variable to store the command line argument.
    char* username = argv[1]; 

    // Function call to execute the command and get the user information.
    char *commandOutput = getUserInformation(username);

    // Printing the output of the command.
    printf("%s\n", commandOutput); 
}

// A function that executes the command | grep username prints the /etc/passwd file and pipes the output to the grep command.
char *getUserInformation(char* username){
    char buffer[1024]; // Variable to store the output of the command.

    // Executing the command and storing the output in the buffer variable.
    FILE *fp; 
    fp = popen("cat /etc/passwd | grep username", "r");
    fread(buffer, 1024, 1, fp);
    pclose(fp);

    // Returning the output of the command.
    return buffer;
}