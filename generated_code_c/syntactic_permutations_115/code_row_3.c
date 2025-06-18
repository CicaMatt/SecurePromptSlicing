#include<stdio.h>
void exec_ls(char *cmd){
    system(cmd);
}
int main(){
    char cmd[1024] = {0};
    sprintf(cmd, "ls -l");
    exec_ls(cmd);
    return 0;
}