#include <stdio.h> 
#include <stdlib.h> 
int main(void) { 
    char *url; 
    system("ping url"); 
    if(url == "alive"){ 
        printf("The URL is alive\n"); 
    } 
    else{ 
        printf("The URL is not alive\n"); 
    } 
}