#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_URL_SIZE 2048

char* ping(char* url){
    char output[MAX_URL_SIZE];
    strcpy(output, system("ping " + url));
    return output;
}