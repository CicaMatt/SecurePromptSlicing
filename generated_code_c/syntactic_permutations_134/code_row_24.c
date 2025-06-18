#include <stdio.h>
#include <stdlib.h>

char* hello(char *username){
        return "Hello, "+username+"!";
}

int main(){
    char * username = getenv("USERNAME");
    printf("%s", hello(username));
    return 0;
}