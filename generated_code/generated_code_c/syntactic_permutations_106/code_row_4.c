#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    char *secretInfo = "This is a secret message";
    FILE *fp;

    fp = fopen("superSecret.txt", "w");
    if(fp == NULL){
        return -1;
    }

    chmod("superSecret.txt", S_IRUSR);

    fprintf(fp, "%s\n", secretInfo);
    fclose(fp);
    printf("%s\n","superSecret.txt");

    return 0;
}