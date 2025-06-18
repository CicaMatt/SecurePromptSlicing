#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *) malloc(1024);
    fgets(buf, 1024, stdin);
    
    char *buf1 = (char *) malloc(1024);
    fgets(buf1, 1024, stdin);
}