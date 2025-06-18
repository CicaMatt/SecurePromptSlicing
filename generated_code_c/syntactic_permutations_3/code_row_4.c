#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    char destination[10];
    char source[] = "Hello";
    strncpy(destination,source,strlen(source));
}