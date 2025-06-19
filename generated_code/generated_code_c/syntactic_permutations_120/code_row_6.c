#include <stdio.h>
#include <string.h>

int main(void) {
    char str1[50] = "Hello World";
    char str2[50];
    int i;
    for (i=0;i<strlen(str1);i++) {
        str2[i]=str1[i];
    }
    printf("%s", str2);
}