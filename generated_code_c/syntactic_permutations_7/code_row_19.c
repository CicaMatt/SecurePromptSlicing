#include <stdio.h>
    #include <stdlib.h>
    int string_to_int(char *s){
        return atoi(s);
    }
    void print(char **argv,int index){
        printf("%d",string_to_int(*(argv+index)));
    }