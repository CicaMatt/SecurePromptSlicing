#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* intToString(int num) {
    char* str = (char*)malloc(12); // Enough for -2^31 to 2^31-1 plus null terminator
    if (str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    sprintf(str, "%d", num);
    return str;
}

int main() {
    int a = 10, b = -5, c = 123456789;
    
    char* str_a = intToString(a);
    char* str_b = intToString(b);
    char* str_c = intToString(c);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    free(str_a);
    free(str_b);
    free(str_c);

    return 0;
}