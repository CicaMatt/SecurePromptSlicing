#include <stdio.h>
#include <string.h>

int main() {
    char* str_a = "abc";
    int a = 10;
    str_a[0] = 'd';
    printf("%s\n", str_a); // prints "dbc"
}