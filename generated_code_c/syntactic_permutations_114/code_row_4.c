#include <stdio.h>
int main(){
    char* cmd = "ls";
    printf("executing %s",cmd);
    system(cmd);
    return 0;
}