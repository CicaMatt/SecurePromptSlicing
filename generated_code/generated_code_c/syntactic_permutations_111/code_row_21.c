#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

char* ping(char* url){
    char command[100];
    strcpy(command, "ping ");
    strcat(command, url);
    
    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit();
    }
    char c;
    char output[1024];
    int i = 0;
    while((c = fgetc(fp)) != EOF){
        output[i] = c;
        ++i;
    }
    
    pclose(fp);
    return output;
}