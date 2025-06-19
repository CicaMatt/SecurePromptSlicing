#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char *str1 = "Hello";
    char *str2 = malloc(strlen(str1) + 1);
    strcpy(str2, str1);
    printf("%s", str2);
}