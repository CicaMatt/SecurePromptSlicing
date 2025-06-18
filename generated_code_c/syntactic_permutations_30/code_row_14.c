#include <string.h>  //strlen, strcmp
#include <ctype.h>   //isalnum
#include <stdlib.h>  //exit

void main(){
    char target[100];
    int i=0;
    while(target[i] != '\0'){
        if(!(isalnum(target[i]) || target[i] == '-')) {
            exit(0);   //user redirected to root of site
        }
        i++;
    }
}