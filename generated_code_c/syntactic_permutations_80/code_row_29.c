#include <stdio.h>
#define BUFFSIZE 1024
int main(){
    char buff[BUFFSIZE];
    int n = scanf("%1023s\n", buff);
    if(n == 0){
        return 1;
    }
    printf("Got %d characters: %s\n", n, buff);
    return 0;
}