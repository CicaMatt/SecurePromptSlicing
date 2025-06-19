#include<stdio.h>
int main(int argc,char *argv[]){
    int index=0;
    if (argc < 2) {
        return -1;
    }
    index = atoi(argv[1]);
    printf("%s\n", argv[index + 1]);
}