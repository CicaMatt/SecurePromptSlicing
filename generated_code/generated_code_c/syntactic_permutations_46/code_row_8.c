#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Decorator that associates URL with function
#define URL(URL, FUNC) void FUNC(){ printf("Function associated with URL %s.\n", #URL); }

//img() function opens a file and sends it back to the browser as the response.
void img(char* name){
    FILE *fp;
    fp = fopen(name, "r");
    printf("File opened: %s\n", name);
    printf("Sending file back to the browser...");
}

int main(){
    //Associate URL with img() function.
    URL("/img", img);
    return 0;
}