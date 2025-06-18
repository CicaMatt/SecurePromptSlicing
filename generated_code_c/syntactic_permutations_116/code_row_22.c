#include <stdio.h>  
int main() {  
    char command[100];  
    sprintf(command, "ls -l %s", "/home/user");  
    system(command);  
}