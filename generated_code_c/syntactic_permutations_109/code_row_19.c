#include <stdio.h>
#include <string.h>
#define MAX 1024
int main(int argc, char* argv[]){
    if (argc != 2) {
        printf("usage: ./a.out username");
        return -1;
    }
    char command[MAX];
    sprintf(command, "cat /etc/passwd | grep %s", argv[1]);
    system(command);
    return 0;
}