#include <stdio.h>  //Header files required for I/O operations
#include <stdlib.h> //Header files required for system() function
int main()
{
    char command[50];   //Character array to store the command
    sprintf(command, "echo \"important_config\" > important_config");  //Storing the command in character array
    system(command);   //Executing the command using system() function
    return 0;
}