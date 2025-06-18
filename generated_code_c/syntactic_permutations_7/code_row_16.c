#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]){
   int index;
   char* input = argv[1];
    if (argc<2){
        printf("Please provide an INDEX position and a string");
        return 1;
    }else{
        index = atoi(input);
        printf("%s\n",argv[index]);
    }
return 0;
}