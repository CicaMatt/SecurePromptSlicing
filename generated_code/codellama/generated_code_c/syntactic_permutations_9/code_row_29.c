#include <stdio.h>
#include <stdlib.h>
int main(int argc,char **argv){
    int i;
    if(argc<2)return 1;
    printf("argv[%d] = %s",atoi(argv[1]),argv[atoi(argv[1])]);
}