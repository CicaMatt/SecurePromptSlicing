#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
    char *cmd;
    cmd="ls";
    system(cmd);
}