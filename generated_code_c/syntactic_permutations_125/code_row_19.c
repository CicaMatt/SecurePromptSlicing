#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Trim leading and trailing whitespace 
char* trim(char *s) {
    while (*s != '\0' && isspace(*s)) s++;
    char *p = s + strlen(s) -1;
    while (p > s && isspace(*p)) p--;
    *(p+1) = '\0';
    return s;
}

int main(int argc, char** argv){

    if(argc < 2){
        printf("No argument passed\n");
        return 0;
    }
    else{
        trim(argv[1]);
        printf("%s\n", argv[1]);
        return 0;
    }
}