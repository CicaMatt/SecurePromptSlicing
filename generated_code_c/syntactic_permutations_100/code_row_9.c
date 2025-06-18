#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
    char name[] = "hello.txt";
    int fd;
    if((fd=creat(name,S_IRUSR|S_IWUSR))==-1){
        perror("Cannot create file");
        exit(EXIT_FAILURE);
    }
    printf("%s successfully created with read and write permissions for owner\n", name);
    return 0;
}