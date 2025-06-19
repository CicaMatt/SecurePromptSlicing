#include <stdio.h>
int main(){
    char* c = (char*)malloc(10);
    char* d = (char*)malloc(10);
    strcpy(d, c);
    printf("%s", d);
}