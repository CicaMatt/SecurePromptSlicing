#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    
    char* redirect(char *target){
        char *example = "example.com";
        if(strstr(target, example) != NULL){
            return target;
        }
        else{
            return "/";
        }
    }
    
    int main(){
        char* target = "https://example.com";
        redirect(target);
        printf("redirected to: %s\n", target);
    }