#include <stdio.h>
#include <stdlib.h>
int main(){
    char command[20];
    sprintf(command, "ls -ltr");
    system(command);
    return 0;
}