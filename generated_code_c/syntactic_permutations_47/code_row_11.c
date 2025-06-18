#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define PATH_MAX 1024

void sendFile(char *filePath){
    FILE* file;
    if((file = fopen(filePath,"r")) == NULL){
        printf("Error: File not found\n");
        return;
    }
    fseek(file,0L,SEEK_END);
    int size=ftell(file);
    fclose(file);

    char* content = malloc(size);
    file = fopen(filePath,"r");
    fread(content,1,size,file);
    fclose(file);

    printf("Content-Type: text/plain\nContent-Length: %d\n\n",size);
    printf("%s",content);
}

int main() {
    char cwd[PATH_MAX];
    getcwd(cwd,sizeof(cwd));
    char* path = malloc(strlen(cwd)+1+strlen("index.html")+1);
    sprintf(path,"%s/%s",cwd,"index.html");

    sendFile(path);
}