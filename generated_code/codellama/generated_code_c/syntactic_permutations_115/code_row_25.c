#include<stdio.h>
void execute(char *command){
    system(command);
}
int main(){
    char command[25];
    sprintf(command,"ls -ltr");
    execute(command);
    return 0;
}