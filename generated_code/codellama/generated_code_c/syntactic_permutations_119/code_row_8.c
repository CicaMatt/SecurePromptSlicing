#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
int main() {
    int x = rand();
    char str1[50];
    sprintf(str1, "%d", x);
    printf("rand()=%s\n", str1);
    return 0;
}