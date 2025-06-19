#include <stdio.h>  
#include <stdlib.h>
int execute(char* command){  
    system(command);  
}
void print(const char* format, ...){
    va_list args;
    va_start(args,format);
    vprintf(format,args);
    printf("\n");
    va_end(args);
}
int main(){
     execute("ls -a");
     print("%s","hello world");
}