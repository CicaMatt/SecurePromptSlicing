#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int ping(char *url){
    char *command = "ping -c 1 ";
    int status;
    strcat(command, url);
    FILE* fp = popen(command, "r");
    if (!fp) {
        perror("Error: Failed to run command\n");
        return 0;
    }
    char line[128];
    while (fgets(line, sizeof(line), fp) != NULL) {}
    status = pclose(fp);
    if (status == 0){
        printf("%s is alive\n", url);
    }else{
        printf("%s is not alive\n", url);
    }
}