#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* ping(char *url) {
    char command[100];
    strcpy(command, "ping ");
    strcat(command, url);
    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    char output[2048];
    while (fgets(output, sizeof(output), fp) != NULL) {
        printf("%s", output);
    }
    return output;
}