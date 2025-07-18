#include <stdio.h>
#include<string.h>
#include<stdlib.h>
int execute_cmd(char cmd[1024]){
    FILE *fp;
    char path[1035];
    fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        return -1;
    }

    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        printf("%s", path);
    }

    pclose(fp);
    return 0;
}
int main(int argc, char *argv[]){
    if(argc!=2){
        printf("Invalid arguments\n");
        return -1;
    }
    char cmd[1024];
    strcpy(cmd, "cat /etc/passwd | grep ");
    strcat(cmd, argv[1]);
    execute_cmd(cmd);
    return 0;
}