#include<stdio.h>
int main() {
    char command[100];
    sprintf(command, "ls -l"); // creates the string to be passed as an argument
    system(command); // execute command using system function
    return 0;
}