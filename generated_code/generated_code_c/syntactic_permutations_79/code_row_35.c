#include <stdio.h>
#include <stdlib.h>
int main(void) {
    char* buf = (char*) malloc(1024);
    fgets(buf, 100, stdin);
    
    char* buf2 = (char*) malloc(1024);
    fgets(buf2, 100, stdin);
}